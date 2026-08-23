// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/CharacterRefComponent.h"
#include "PlayerCameraControllerComponent.generated.h"

class UPlayerCameraPrimaryDataAsset;

/**
 * 
 */
UCLASS()
class SPLITSCREEN_API UPlayerCameraControllerComponent : public UCharacterRefComponent
{
	GENERATED_BODY()

protected:
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	TObjectPtr<UPlayerCameraPrimaryDataAsset> PlayerCameraDataAsset;

private:
	float CameraLookSpeed;

public:
	void ReceiveLookInput(FVector2D LookInput);

	void BeginPlay() override;
};
