// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseUiSystemComponent.h"
#include "FullscreenUiSystemComponent.generated.h"

/**
 * 
 */
UCLASS()
class SPLITSCREEN_API UFullscreenUiSystemComponent : public UBaseUiSystemComponent
{
	GENERATED_BODY()

protected:
	void Internal_AddWidgetToViewport(UUserWidget* Widget) override;
};
