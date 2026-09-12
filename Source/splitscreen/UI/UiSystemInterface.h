// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "UiSystemInterface.generated.h"

class UUserWidget;
class ULocalPlayer;

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UUiSystemInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class SPLITSCREEN_API IUiSystemInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual void AddWidgetToEntireViewport(UUserWidget* Widget) PURE_VIRTUAL(IUiSystemInterface::AddWidgetToEntireViewport,);

	virtual void AddWidgetToLocalPlayerScreen(UUserWidget* Widget, ULocalPlayer* LocalPlayer) PURE_VIRTUAL(IUiSystemInterface::AddWidgetToLocalPlayerScreen,);

	virtual void RemoveWidgetFromEntireViewport(UUserWidget* Widget) PURE_VIRTUAL(IUiSystemInterface::RemoveWidgetFromEntireViewport,);

	virtual void RemoveWidgetFromLocalPlayerScreen(UUserWidget* Widget, ULocalPlayer* LocalPlayer) PURE_VIRTUAL(IUiSystemInterface::RemoveWidgetFromLocalPlayerScreen,);
};
