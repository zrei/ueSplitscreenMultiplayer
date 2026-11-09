// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseUiSystemComponent.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/PlayerController.h"
#include "Core/Component Ledger/CoreInterface.h"
#include "Input/InputControllerInterface.h"
#include "UI/Widget/Base/FocusableWidget.h"
#include "Core/Component Ledger/CoreHelper.h"
#include "Common/Macros/ErrorMacros.h"

void UBaseUiSystemComponent::AddWidgetToViewport(UUserWidget* Widget, bool HideOthers) {
	if (HideOthers && !this->IsUiStackEmpty()) {
		for (UUserWidget* RemovedWidget : this->UiStack) {
			if (RemovedWidget->IsInViewport()) {
				UFocusableWidget* RemovedFocusableWidget = Cast<UFocusableWidget>(RemovedWidget);
				if (RemovedFocusableWidget) {
					RemovedFocusableWidget->NativeOnWidgetHide();
				}
				RemovedWidget->RemoveFromParent();
			}
		}
	}

	UFocusableWidget* FocusableWidget = Cast<UFocusableWidget>(Widget);
	if (FocusableWidget) {
		FocusableWidget->NativeOnWidgetOpen();
	}

	Internal_AddWidgetToViewport(Widget);
	Widget->SetFocus();
	UiStack.Push(Widget);

	this->OnWidgetOpened.Broadcast(Widget);

	if (UiStack.Num() == 1) {
		APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
		IInputControllerInterface* InputController = NULL;
		if (PlayerController && UCoreHelper::GetInterfaceComponentFromUObject(PlayerController, UInputControllerInterface::StaticClass(), InputController)) {
			InputController->SwitchToUIInput(Widget, EMouseLockMode::DoNotLock);
		}

		this->OnUiStackFirstOpened.Broadcast();
	}
}

bool UBaseUiSystemComponent::RemoveWidgetFromViewport(UUserWidget* Widget) {
	int widgetIndex = this->GetWidgetStackIndex(Widget);
	if (widgetIndex < 0) {
		return false;
	}
	bool isTop = this->UiStack.Num() == widgetIndex + 1;

	this->UiStack.RemoveAt(widgetIndex);
	this->Internal_RemoveWidgetFromViewport(Widget, isTop);
	return true;
}

bool UBaseUiSystemComponent::PopTopWidgetFromViewport() {
	if (this->IsUiStackEmpty()) {
		return false;
	}

	UUserWidget* WidgetToRemove = this->UiStack.Pop();
	this->Internal_RemoveWidgetFromViewport(WidgetToRemove, true);
	return true;
}

void UBaseUiSystemComponent::Internal_RemoveWidgetFromViewport(UUserWidget* WidgetToRemove, bool IsTopLayer) {
	UFocusableWidget* FocusableWidgetToRemove = Cast<UFocusableWidget>(WidgetToRemove);
	if (FocusableWidgetToRemove) {
		FocusableWidgetToRemove->NativeOnWidgetClose();
	}
	WidgetToRemove->RemoveFromParent();
	this->OnWidgetClosed.Broadcast(WidgetToRemove);

	if (IsTopLayer && !this->IsUiStackEmpty()) {
		UUserWidget* WidgetToReopen = this->UiStack.Last();
		if (!WidgetToReopen->IsInViewport()) {
			UFocusableWidget* FocusableWidgetToReopen = Cast<UFocusableWidget>(WidgetToReopen);
			if (FocusableWidgetToReopen) {
				FocusableWidgetToReopen->NativeOnWidgetReopened();
			}
			this->Internal_AddWidgetToViewport(WidgetToReopen);
			WidgetToReopen->SetFocus();
		}
	}
	
	if (this->IsUiStackEmpty()) {
		// switch input back to game
		APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
		IInputControllerInterface* InputController = NULL;
		if (PlayerController && UCoreHelper::GetInterfaceComponentFromUObject(PlayerController, UInputControllerInterface::StaticClass(), InputController)) {
			InputController->SwitchToGameInput();
		}

		this->OnUiStackFullyClosed.Broadcast();
	}
}

bool UBaseUiSystemComponent::IsUiStackEmpty() {
	return this->UiStack.IsEmpty();
}

int UBaseUiSystemComponent::GetWidgetStackIndex(UUserWidget* Widget) {
	for (size_t i = 0; i < this->UiStack.Num(); i++) {
		if (this->UiStack[i] == Widget) {
			return i;
		}
	}
	return -1;
}

bool UBaseUiSystemComponent::IsWidgetInStack(UUserWidget* Widget) {
	return this->GetWidgetStackIndex(Widget) > -1;
}

bool UBaseUiSystemComponent::IsIgnoredInputKey(FKey Key) {
	return this->IgnoredInputKeys.Contains(Key);
}

void UBaseUiSystemComponent::OnKeyPressed(FKey Key) {
	this->OnUiKeyPressed.Broadcast(Key);
}