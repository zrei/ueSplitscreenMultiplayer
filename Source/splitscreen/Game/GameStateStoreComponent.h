// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Core/BaseActorComponent.h"
#include "GameStateStoreComponent.generated.h"

UENUM()
enum FInputState : uint8
{
	InputState_NONE, // still init
	InputState_GAME, // playing
	InputState_UI, // on UI
};

/**
 * 
 */
UCLASS()
class SPLITSCREEN_API UGameStateStoreComponent : public UBaseActorComponent
{
	GENERATED_BODY()
	
private:
	bool IsGamePaused = true;

	FInputState CurrInputState = FInputState::InputState_NONE;
};
