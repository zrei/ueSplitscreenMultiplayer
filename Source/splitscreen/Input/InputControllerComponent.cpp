// Fill out your copyright notice in the Description page of Project Settings.


#include "Input/InputControllerComponent.h"
#include "GameFramework/PlayerController.h"
#include "Components/Widget.h"
#include "Common/Macros/ErrorMacros.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "UserSettings/EnhancedInputUserSettings.h"

UInputControllerComponent::UInputControllerComponent() {
	AActor* Owner = this->GetOwner();

	if (!Owner)
		return;

	ControllerRef = Cast<APlayerController>(Owner);
	
	if (!ControllerRef) {
		LOG_ERROR_AND_RETURN_VOID(TEXT("Input Controller Component"), TEXT("Cannot find controller ref!"));
	}

	InputSubsystemRef = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(ControllerRef->GetLocalPlayer());

	if (!InputSubsystemRef) {
		LOG_ERROR_AND_RETURN_VOID(TEXT("Input Controller Component"), TEXT("Cannot find input subsystem ref!"));
	}

	InputUserSettingsRef = InputSubsystemRef->GetUserSettings();

	if (!InputUserSettingsRef) {
		LOG_ERROR_AND_RETURN_VOID(TEXT("Input Controller Component"), TEXT("Cannot find input user settings ref!"));
	}

	InputUserSettingsRef->RegisterInputMappingContext(GameInputMap);
}

void UInputControllerComponent::SwitchToUIInput(UWidget* InWidgetToFocus, EMouseLockMode InMouseLockMode) {
	FInputModeUIOnly InputMode;
	InputMode.SetLockMouseToViewportBehavior(InMouseLockMode);

	if (InWidgetToFocus != nullptr)
	{
		InputMode.SetWidgetToFocus(InWidgetToFocus->TakeWidget());
	}
	ControllerRef->SetInputMode(InputMode);

	ControllerRef->FlushPressedKeys();
	
	SwitchToUIInputMap();
}

void UInputControllerComponent::SwitchToGameInput() {
	FInputModeGameOnly InputMode;
	ControllerRef->SetInputMode(InputMode);

	ControllerRef->FlushPressedKeys();

	SwitchToGameInputMap();
}

void UInputControllerComponent::SwitchToUIInputMap() {
	InputSubsystemRef->RemoveMappingContext(GameInputMap);
	InputSubsystemRef->RemoveMappingContext(DebugInputMap);
	InputSubsystemRef->AddMappingContext(UIInputMap, 0);
}

void UInputControllerComponent::SwitchToGameInputMap() {
	InputSubsystemRef->RemoveMappingContext(UIInputMap);
	InputSubsystemRef->AddMappingContext(GameInputMap, 1);

#if !UE_BUILD_SHIPPING
	InputSubsystemRef->AddMappingContext(DebugInputMap, 0);
#endif
}