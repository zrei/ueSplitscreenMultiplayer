// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "PlayerMovementPrimaryDataAsset.generated.h"

/**
 * 
 */
UCLASS()
class SPLITSCREEN_API UPlayerMovementPrimaryDataAsset : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	float PlayerMovementSpeed;
};
