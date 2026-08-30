// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Core/BaseActorComponent.h"
#include "SplitscreenControllerInterface.h"
#include "SplitscreenControllerComponent.generated.h"

/**
 * 
 */
UCLASS()
class SPLITSCREEN_API USplitscreenControllerComponent : public UBaseActorComponent, public ISplitscreenControllerInterface
{
	GENERATED_BODY()
	
public:
	void ToggleSplitscreen(bool ToggleOn) override;
};
