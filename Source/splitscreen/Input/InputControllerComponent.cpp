// Fill out your copyright notice in the Description page of Project Settings.


#include "Input/InputControllerComponent.h"
#include "GameFramework/PlayerController.h"
#include "Components/Widget.h"
#include "Common/Macros/ErrorMacros.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "UserSettings/EnhancedInputUserSettings.h"

#define NO_POSSESSED_PAWN_RETURN(ret) if (!this->ControllerHasPossessedPlayer) { ULogger::LogErrorToScreen(TEXT("Controller does not have possessed pawn")); return ret; }

UInputControllerComponent::UInputControllerComponent() {
	AActor* Owner = this->GetOwner();

	if (!Owner)
		return;

	ControllerRef = Cast<APlayerController>(Owner);

	CHECK_POINTER_IF_NULL_LOG_ERRROR_AND_RETURN_VOID(this->ControllerRef, TEXT("Input Controller Component"), TEXT("Cannot find controller ref!"))
}

void UInputControllerComponent::InitForNewPawn() {
	ULocalPlayer* LocalPlayer = ControllerRef->GetLocalPlayer();

	this->ControllerHasPossessedPlayer = LocalPlayer != NULL;

	CHECK_POINTER_IF_NULL_LOG_ERRROR_AND_RETURN_VOID(LocalPlayer, TEXT("Input Controller Component"), TEXT("Cannot find local player!"))

	InputSubsystemRef = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(LocalPlayer);

	CHECK_POINTER_IF_NULL_LOG_ERRROR_AND_RETURN_VOID(InputSubsystemRef, TEXT("Input Controller Component"), TEXT("Cannot find input subsystem ref!"))

	this->SwitchToGameInput();
}

void UInputControllerComponent::SwitchToUIInput(UWidget* InWidgetToFocus, EMouseLockMode InMouseLockMode) {
	NO_POSSESSED_PAWN_RETURN()

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
	NO_POSSESSED_PAWN_RETURN()

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

UEnhancedInputUserSettings* UInputControllerComponent::GetUserInputSettings() {
	NO_POSSESSED_PAWN_RETURN(NULL)

	if (this->InputUserSettingsRef)
		return this->InputUserSettingsRef;

	CHECK_POINTER_IF_NULL_LOG_ERROR_AND_RETURN_NULL(this->InputSubsystemRef, TEXT("Input Controller Component"), TEXT("No input subsystem ref to pull user input settings from"))

	this->InputUserSettingsRef = InputSubsystemRef->GetUserSettings();

	CHECK_POINTER_IF_NULL_LOG_ERROR_AND_RETURN_NULL(this->InputUserSettingsRef, TEXT("Input Controller Component"), TEXT("Cannot find input user settings ref!"))

	return this->InputUserSettingsRef;
}

void UInputControllerComponent::ToggleKeyBindingMode(bool ToggleOn) {
	if (ToggleOn && !this->GetUserInputSettings()->IsMappingContextRegistered(this->GameInputMap)) {
		this->GetUserInputSettings()->RegisterInputMappingContext(this->GameInputMap);
	}
	else if (!ToggleOn && this->GetUserInputSettings()->IsMappingContextRegistered(this->GameInputMap)) {
		this->GetUserInputSettings()->UnregisterInputMappingContext(this->GameInputMap);
	}
}
