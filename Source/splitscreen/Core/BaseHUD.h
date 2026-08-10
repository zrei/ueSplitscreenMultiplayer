// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "Component Ledger/CoreInterface.h"
#include "BaseHUD.generated.h"

/**
 * 
 */
UCLASS()
class SPLITSCREEN_API ABaseHUD : public AHUD, public ICoreInterface
{
	GENERATED_BODY()

public:
	ABaseHUD();

protected:
	UPROPERTY(VisibleAnywhere)
	UComponentLedger* ComponentLedger;

	UComponentLedger* GetComponentLedger() override;
	
};
