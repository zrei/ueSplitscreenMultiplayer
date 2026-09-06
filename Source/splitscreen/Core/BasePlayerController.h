// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Component Ledger/CoreInterface.h"
#include "BasePlayerController.generated.h"

class UInputControllerComponent;

/**
 * 
 */
UCLASS()
class SPLITSCREEN_API ABasePlayerController : public APlayerController, public ICoreInterface
{
	GENERATED_BODY()

public:
	ABasePlayerController();

protected:
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UComponentLedger> ComponentLedger;

	UComponentLedger* GetComponentLedger() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UInputControllerComponent> InputController;

	void OnPossess(APawn* aPawn) override;
};
