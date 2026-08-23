// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "Component Ledger/CoreInterface.h"
#include "BaseGameMode.generated.h"

/**
 * 
 */
UCLASS()
class SPLITSCREEN_API ABaseGameMode : public AGameMode, public ICoreInterface
{
	GENERATED_BODY()

public:
	ABaseGameMode();

protected:
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UComponentLedger> ComponentLedger;
	
	UComponentLedger* GetComponentLedger() override;
};
