// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "InputControllerInterface.generated.h"

class UWidget;

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UInputControllerInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class SPLITSCREEN_API IInputControllerInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual void SwitchToUIInput(UWidget* InWidgetToFocus, EMouseLockMode InMouseLockMode) PURE_VIRTUAL(IInputControllerInterface::SwitchToUIInput, );

	virtual void SwitchToGameInput() PURE_VIRTUAL(IInputControllerInterface::SwitchToGameInput, );
};
