// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Core/BaseActorComponent.h"
#include "InputControllerInterface.h"
#include "InputControllerComponent.generated.h"

class APlayerController;
class UWidget;
class UInputMappingContext;
class UEnhancedInputLocalPlayerSubsystem;
class UEnhancedInputUserSettings;

/**
 * Component that should sit on the player controller in order to affect multiple local players. Will need handling for networked multiplayer in the future.
 */
UCLASS()
class SPLITSCREEN_API UInputControllerComponent : public UBaseActorComponent, public IInputControllerInterface
{
	GENERATED_BODY()

public:
	void SwitchToUIInput(UWidget* InWidgetToFocus, EMouseLockMode InMouseLockMode = EMouseLockMode::DoNotLock) override;

	void SwitchToGameInput() override;

	void Init();

protected:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TObjectPtr<UInputMappingContext> GameInputMap;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TObjectPtr<UInputMappingContext> DebugInputMap;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TObjectPtr<UInputMappingContext> UIInputMap;

private:
	void SwitchToGameInputMap();

	void SwitchToUIInputMap();

private:
	TObjectPtr<APlayerController> ControllerRef;

	TObjectPtr<UEnhancedInputLocalPlayerSubsystem> InputSubsystemRef;

	TObjectPtr<UEnhancedInputUserSettings> InputUserSettingsRef;
};
