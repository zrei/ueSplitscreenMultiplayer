// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Core/Component Ledger/CoreInterface.h"
#include "BasePlayerCharacter.generated.h"

class UInputAction;
struct FInputActionValue;
class UPlayerMovementComponent;
class UPlayerCameraControllerComponent;

UCLASS()
class SPLITSCREEN_API ABasePlayerCharacter : public ACharacter, public ICoreInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABasePlayerCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UComponentLedger> ComponentLedger;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TObjectPtr<UInputAction> MoveInputAction;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TObjectPtr<UInputAction> LookInputAction;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UPlayerMovementComponent> PlayerMovementComponent;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UPlayerCameraControllerComponent> PlayerCameraControllerComponent;

	UPROPERTY(BlueprintReadOnly)
	FVector2D CurrLookInput;

	UPROPERTY(BlueprintReadOnly)
	FVector2D CurrMoveInput;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	void LookAction(const FInputActionValue& LookValue);

	void MoveAction(const FInputActionValue& MoveValue);

protected:
	UComponentLedger* GetComponentLedger() override;
};
