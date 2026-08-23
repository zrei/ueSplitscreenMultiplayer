// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameSession.h"
#include "Component Ledger/CoreInterface.h"
#include "BaseGameSession.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class SPLITSCREEN_API ABaseGameSession : public AGameSession, public ICoreInterface
{
	GENERATED_BODY()

public:
	ABaseGameSession();

protected:
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UComponentLedger> ComponentLedger;

	UComponentLedger* GetComponentLedger() override;
	
};
