// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "UiSystemInterface.generated.h"

class UUserWidget;
class ULocalPlayer;

// This class does not need to be modified.
UINTERFACE(MinimalAPI, NotBlueprintable)
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
	virtual void AddWidgetToViewport(UUserWidget* Widget, bool HideOthers) PURE_VIRTUAL(IUiSystemInterface::AddWidgetToViewport,);

	virtual bool RemoveWidgetFromViewport(UUserWidget* Widget) PURE_VIRTUAL(IUiSystemInterface::RemoveWidgetFromViewport, return false;);

	virtual bool PopTopWidgetFromViewport() PURE_VIRTUAL(IUiSystemInterface::PopTopWidgetFromViewport, return false;);

	virtual bool IsUiStackEmpty() PURE_VIRTUAL(IUiSystemInterface::IsStackEmpty, return false;);

	virtual int GetWidgetStackIndex(UUserWidget* Widget) PURE_VIRTUAL(IUiSystemInterface::GetWidgetStackIndex, return -1;);

	virtual bool IsWidgetInStack(UUserWidget* Widget) PURE_VIRTUAL(IUiSystemInterface::IsWidgetInStacl, return false;);

	virtual bool IsIgnoredInputKey(FKey Key) PURE_VIRTUAL(IUiSystemInterface::IsIgnoredInputKey, return false;);

	virtual void OnKeyPressed(FKey Key) PURE_VIRTUAL(IUiSystemInterface::OnKeyPressed, );
};
