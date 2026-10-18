// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Core/BaseActorComponent.h"
#include "UiSystemInterface.h"
#include "UiSystemComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FUserWidgetEvent, UUserWidget*, Widget);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FUiSystemEvent);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FUiKeyEvent, FKey, Key);

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

	bool IsIgnoredInputKey(FKey Key) override;

	void OnKeyPressed(FKey Key) override;

public:
	UFUNCTION(BlueprintCallable)
	bool IsUiStackEmpty();

public:
	UPROPERTY(BlueprintAssignable)
	FUserWidgetEvent OnWidgetOpened;

	UPROPERTY(BlueprintAssignable)
	FUserWidgetEvent OnWidgetClosed;

	UPROPERTY(BlueprintAssignable)
	FUiSystemEvent OnUiStackFirstOpened;

	UPROPERTY(BlueprintAssignable)
	FUiSystemEvent OnUiStackFullyClosed;

	UPROPERTY(BlueprintAssignable)
	FUiKeyEvent OnUiKeyPressed;

protected:
	UPROPERTY(BlueprintReadWrite)
	TArray<FKey> IgnoredInputKeys;

private:
	TArray<UUserWidget*> UiStack{};
};
