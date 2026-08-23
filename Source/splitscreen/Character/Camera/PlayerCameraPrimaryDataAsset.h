// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "PlayerCameraPrimaryDataAsset.generated.h"

/**
 * 
 */
UCLASS()
class SPLITSCREEN_API UPlayerCameraPrimaryDataAsset : public UPrimaryDataAsset
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	float CameraLookSpeed;
};
