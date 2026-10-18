// Fill out your copyright notice in the Description page of Project Settings.


#include "FocusableWidget.h"
#include "UI/UiSystemInterface.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/GameStateBase.h"
#include "Common/Logger.h"
#include "Core/Component Ledger/CoreHelper.h"

UFocusableWidget::UFocusableWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
	bIsFocusable = true;
}

void UFocusableWidget::NativeOnWidgetOpen() {
	if (this->OpenSound)
		UGameplayStatics::PlaySound2D(this, this->OpenSound);

	this->OnWidgetOpen();

	this->OnWidgetOpened.Broadcast();
}

void UFocusableWidget::NativeOnWidgetClose() {
	if (this->CloseSound)
		UGameplayStatics::PlaySound2D(this, this->CloseSound);

	this->OnWidgetClose();

	this->OnWidgetClosed.Broadcast();
}

void UFocusableWidget::NativeOnWidgetReopened() {
	if (this->PlayOpenSoundOnReopen && this->OpenSound)
		UGameplayStatics::PlaySound2D(this, this->OpenSound);

	this->OnWidgetReopened();
}

void UFocusableWidget::NativeOnWidgetHide() {
	this->OnWidgetHide();
}

void UFocusableWidget::NativeConstruct() {
	UUserWidget::NativeConstruct();

	this->NativeSetCustomNavigation();
}

FReply UFocusableWidget::NativeOnFocusReceived(const FGeometry& InGeometry, const FFocusEvent& InFocusEvent) {
	this->NativeSetInitialFocus();

	return UUserWidget::NativeOnFocusReceived(InGeometry, InFocusEvent);
}

FReply UFocusableWidget::NativeOnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent) {
	this->NativeHandleKeyActivated(InKeyEvent.GetKey());
	return UUserWidget::NativeOnKeyDown(InGeometry, InKeyEvent);
}

FReply UFocusableWidget::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) {
	this->NativeHandleKeyActivated(InMouseEvent.GetEffectingButton());
	return UUserWidget::NativeOnMouseButtonDown(InGeometry, InMouseEvent);
}

FReply UFocusableWidget::NativeOnAnalogValueChanged(const FGeometry& InGeometry, const FAnalogInputEvent& InAnalogEvent) {
	if (InAnalogEvent.GetAnalogValue() > this->AnalogStickMoveErrorThresholdSquared) {
		this->TrySwitchControlMode(false);
		this->NativeDoScroll(InAnalogEvent.GetAnalogValue());
	}
	return UUserWidget::NativeOnAnalogValueChanged(InGeometry, InAnalogEvent);
}

FReply UFocusableWidget::NativeOnMouseMove(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) {
	if (InMouseEvent.GetCursorDelta().SquaredLength() > this->MouseMoveErrorThresholdSquared) {
		this->TrySwitchControlMode(true);
	}
	return UUserWidget::NativeOnMouseMove(InGeometry, InMouseEvent);
}

void UFocusableWidget::NativeHandleKeyActivated(const FKey& Key) {
	AGameStateBase* GameState = UGameplayStatics::GetGameState(GetWorld());
	IUiSystemInterface* UiController = NULL;
	if (GameState && UCoreHelper::GetInterfaceComponentFromUObject(GameState, UUiSystemInterface::StaticClass(), UiController) && UiController->IsIgnoredInputKey(Key)) {
		return;
	}

	this->TrySwitchControlMode(!Key.IsGamepadKey());

	if (Key == this->ManualCloseKey && this->CanManuallyClose) {
		this->TryCloseWidget();
		return;
	}

	UiController->OnKeyPressed(Key);
	this->HandleKeyActivated(Key);
}

bool UFocusableWidget::NativeCanCloseWidget() {
	return this->CanCloseWidget();
}

bool UFocusableWidget::CanCloseWidget_Implementation() {
	return true;
}

void UFocusableWidget::NativeSetInitialFocus() {
	this->SetInitialFocus();
}

bool UFocusableWidget::TryCloseWidget() {
	if (!this->NativeCanCloseWidget()) {
		return false;
	}

	this->CloseWidget();
	return true;
}

void UFocusableWidget::NativeDoScroll(float ScrollAmount) {
	for (UScrollBox* ScrollBox : this->ScrollBoxes) {
		ScrollBox->SetScrollOffset(ScrollBox->GetScrollOffset() + ScrollAmount * 0.2);
	}
	this->DoScroll(ScrollAmount);
}

void UFocusableWidget::NativeSetCustomNavigation() {
	this->SetCustomNavigation();
}

void UFocusableWidget::SetDelay(FName Key, float Delay) {
	this->CancelCurrDelay();
	float DelayAnimLength = 1.0f; /// assumed
	// DelayAnimLength = this->GetPlayLength(this->DelayAnimation);
	float PlaybackSpeed = DelayAnimLength / Delay;
	this->DelayAnimationHandle = this->PlayAnimationForward(DelayAnimation, PlaybackSpeed);
	this->CurrDelayKey = Key;
}

void UFocusableWidget::CancelCurrDelay() {
	this->HasCancelledDelay = true;
	this->StopAnimation(this->DelayAnimation);
	this->HasCancelledDelay = false;
	// empty out delay key
	this->CurrDelayKey = FName();
}

void UFocusableWidget::CancelSpecificDelay(FName DelayKey) {
	if (this->CurrDelayKey != DelayKey) {
		ULogger::LogWarningToScreen(TEXT("Delay key does not match current delay"));
		return;
	}

	this->CancelCurrDelay();
}

void UFocusableWidget::OnAnimationFinished_Implementation(const UWidgetAnimation* Animation) {
	if (Animation && Animation == this->DelayAnimation) {
		this->OnDelayAnimComplete();
	}

	UUserWidget::OnAnimationFinished_Implementation(Animation);
}

void UFocusableWidget::OnDelayAnimComplete() {
	if (this->HasCancelledDelay)
		return;

	this->NativeOnDelayCompleteEvent(this->CurrDelayKey);
	// empty out delay key
	this->CurrDelayKey = FName();
}

void UFocusableWidget::NativeOnDelayCompleteEvent(FName Key) {
	this->OnDelayCompleteEvent(Key);
}

void UFocusableWidget::CloseWidget() {
	AGameStateBase* GameState = UGameplayStatics::GetGameState(GetWorld());
	IUiSystemInterface* UiController = NULL;
	if (GameState && UCoreHelper::GetInterfaceComponentFromUObject(GameState, UUiSystemInterface::StaticClass(), UiController)) {
		UiController->RemoveWidgetFromEntireViewport(this);
	}
}

void UFocusableWidget::NativeOnSwitchToKBM() {
	this->IsKBM = true;
	this->OnSwitchToKBM();
}

void UFocusableWidget::NativeOnSwitchToGamepad() {
	this->IsKBM = false;
	this->OnSwitchToGamepad();
}

void UFocusableWidget::TrySwitchControlMode(bool bIsKBM) {
	if (this->IsKBM == bIsKBM)
		return;

	if (bIsKBM)
		this->NativeOnSwitchToKBM();
	else
		this->NativeOnSwitchToGamepad();
}

void UFocusableWidget::SwitchScrollViewInputMode() {
	for (UScrollBox* ScrollBox : this->ScrollBoxes) {
		if (this->IsKBM) {

		}
		else {

		}
	}
}