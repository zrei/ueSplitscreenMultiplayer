// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "SplitscreenControllerInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class USplitscreenControllerInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class SPLITSCREEN_API ISplitscreenControllerInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual void ToggleSplitscreen(bool ToggleOn) PURE_VIRTUAL(ISplitscreenControllerInterface::ToggleSplitscreen, );
};
