// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameState.h"
#include "Component Ledger/CoreInterface.h"
#include "BaseGameState.generated.h"

class USplitscreenController;

/**
 * 
 */
UCLASS()
class SPLITSCREEN_API ABaseGameState : public AGameState, public ICoreInterface
{
	GENERATED_BODY()

public:
	ABaseGameState();

protected:
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UComponentLedger> ComponentLedger;

	UComponentLedger* GetComponentLedger() override;

	UPROPERTY(VisibleAnywhere)
	USplitscreenController* SplitscreenControllerComponent;
};
