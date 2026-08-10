// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "Component Ledger/CoreInterface.h"
#include "BasePlayerState.generated.h"

/**
 * 
 */
UCLASS()
class SPLITSCREEN_API ABasePlayerState : public APlayerState, public ICoreInterface
{
	GENERATED_BODY()
	
public:
	ABasePlayerState();

protected:
	UPROPERTY(VisibleAnywhere)
	UComponentLedger* ComponentLedger;

	UComponentLedger* GetComponentLedger() override;
};
