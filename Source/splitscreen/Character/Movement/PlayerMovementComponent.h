// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/CharacterRefComponent.h"
#include "PlayerMovementComponent.generated.h"

class UPlayerMovementPrimaryDataAsset;
/**
 * 
 */
UCLASS()
class SPLITSCREEN_API UPlayerMovementComponent : public UCharacterRefComponent
{
	GENERATED_BODY()

protected:
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	TObjectPtr<UPlayerMovementPrimaryDataAsset> PlayerMovementDataAsset;

private:
	float MoveSpeed;

	FVector CurrMoveVector;

public:
	void ReceiveMoveInput(FVector2D MoveInput);

	void BeginPlay() override;
};
