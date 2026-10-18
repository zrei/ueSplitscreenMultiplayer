// Fill out your copyright notice in the Description page of Project Settings.


#include "UiSystemComponent.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/PlayerController.h"
#include "Core/Component Ledger/CoreInterface.h"
#include "Input/InputControllerInterface.h"
#include "UI/Widget/Base/FocusableWidget.h"
#include "Core/Component Ledger/CoreHelper.h"
#include "Common/Macros/ErrorMacros.h"

void UUiSystemComponent::AddWidgetToEntireViewport(UUserWidget* Widget) {
	if (!this->IsUiStackEmpty()) {
		UUserWidget* RemovedWidget = this->UiStack.Last();
		UFocusableWidget* RemovedFocusableWidget = Cast<UFocusableWidget>(RemovedWidget);
		if (RemovedFocusableWidget) {
			RemovedFocusableWidget->NativeOnWidgetHide();
		}
		RemovedWidget->RemoveFromParent();
	}

	UFocusableWidget* FocusableWidget = Cast<UFocusableWidget>(Widget);
	if (FocusableWidget) {
		FocusableWidget->NativeOnWidgetOpen();
	}
	Widget->AddToViewport();
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

void UUiSystemComponent::AddWidgetToLocalPlayerScreen(UUserWidget* Widget, ULocalPlayer* LocalPlayer) {

}

void UUiSystemComponent::RemoveWidgetFromEntireViewport(UUserWidget* Widget) {
	if (this->IsUiStackEmpty()) {
		LOG_ERROR_AND_RETURN_VOID(TEXT("UI System"), TEXT("Ui stack is empty! Nothing to remove!"))
	}

	UUserWidget* WidgetToRemove = this->UiStack.Pop();
	UFocusableWidget* FocusableWidgetToRemove = Cast<UFocusableWidget>(WidgetToRemove);
	if (FocusableWidgetToRemove) {
		FocusableWidgetToRemove->NativeOnWidgetClose();
	}
	WidgetToRemove->RemoveFromParent();
	this->OnWidgetClosed.Broadcast(WidgetToRemove);
	
	if (!this->IsUiStackEmpty()) {
		UUserWidget* WidgetToReopen = this->UiStack.Last();
		UFocusableWidget* FocusableWidgetToReopen = Cast<UFocusableWidget>(WidgetToReopen);
		if (FocusableWidgetToReopen) {
			FocusableWidgetToReopen->NativeOnWidgetReopened();
		}
		WidgetToReopen->AddToViewport();
		WidgetToReopen->SetFocus();
	}
	else {
		// switch input back to game
		APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
		IInputControllerInterface* InputController = NULL;
		if (PlayerController && UCoreHelper::GetInterfaceComponentFromUObject(PlayerController, UInputControllerInterface::StaticClass(), InputController)) {
			InputController->SwitchToGameInput();
		}

		this->OnUiStackFullyClosed.Broadcast();
	}
}

void UUiSystemComponent::RemoveWidgetFromLocalPlayerScreen(UUserWidget* Widget, ULocalPlayer* LocalPlayer) {

}

bool UUiSystemComponent::IsUiStackEmpty() {
	return this->UiStack.IsEmpty();
}

bool UUiSystemComponent::IsIgnoredInputKey(FKey Key) {
	return this->IgnoredInputKeys.Contains(Key);
}

void UUiSystemComponent::OnKeyPressed(FKey Key) {
	this->OnUiKeyPressed.Broadcast(Key);
}