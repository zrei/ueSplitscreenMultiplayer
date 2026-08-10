// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Core/Component Ledger/CoreInterface.h"
#include "BasePlayerCharacter.generated.h"

class UInputAction;
struct FInputActionValue;

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
	UComponentLedger* ComponentLedger;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UInputAction* MoveInputAction;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UInputAction* LookInputAction;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float MoveSpeed;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float LookSpeed;

	UPROPERTY(BlueprintReadOnly)
	FVector2D CurrLookInput;

	UPROPERTY(BlueprintReadOnly)
	FVector2D CurrMoveInput;

	UPROPERTY(BlueprintReadOnly)
	FVector CurrMoveVector;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	void LookAction(const FInputActionValue& LookValue);

	void MoveAction(const FInputActionValue& MoveValue);

protected:
	UFUNCTION(BlueprintImplementableEvent)
	void OnLookAction(FVector2D lookVector);

	UFUNCTION(BlueprintImplementableEvent)
	void OnMoveAction(FVector2D MoveInput, FVector MoveVector);

	UComponentLedger* GetComponentLedger() override;
};
