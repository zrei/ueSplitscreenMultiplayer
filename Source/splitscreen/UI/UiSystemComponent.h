// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Core/BaseActorComponent.h"
#include "UiSystemInterface.h"
#include "UiSystemComponent.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FUserWidgetEvent, UUserWidget*)
DECLARE_MULTICAST_DELEGATE(FUiSystemEvent)

/**
 * 
 */
UCLASS()
class SPLITSCREEN_API UUiSystemComponent : public UBaseActorComponent, public IUiSystemInterface
{
	GENERATED_BODY()
	
public:
	void AddWidgetToEntireViewport(UUserWidget* Widget) override;

	void AddWidgetToLocalPlayerScreen(UUserWidget* Widget, ULocalPlayer* LocalPlayer) override;

	void RemoveWidgetFromEntireViewport(UUserWidget* Widget) override;

	void RemoveWidgetFromLocalPlayerScreen(UUserWidget* Widget, ULocalPlayer* LocalPlayer) override;

public:
	FUserWidgetEvent OnWidgetOpened;

	FUserWidgetEvent OnWidgetClosed;

	FUiSystemEvent OnUiStackFirstOpened;

	FUiSystemEvent OnUiStackFullyClosed;

private:
	TArray<UUserWidget*> UiStack{};
};
