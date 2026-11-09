// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Core/BaseActorComponent.h"
#include "UiSystemInterface.h"
#include "BaseUiSystemComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FUserWidgetEvent, UUserWidget*, Widget);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FUiSystemEvent);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FUiKeyEvent, FKey, Key);

/**
 * 
 */
UCLASS(Abstract)
class SPLITSCREEN_API UBaseUiSystemComponent : public UBaseActorComponent, public IUiSystemInterface
{
	GENERATED_BODY()
	
public:
	void AddWidgetToViewport(UUserWidget* Widget, bool HideOthers) override;

	bool RemoveWidgetFromViewport(UUserWidget* Widget) override;
	
	bool PopTopWidgetFromViewport() override;
	
	bool IsUiStackEmpty() override;
	
	int GetWidgetStackIndex(UUserWidget* Widget) override;

	bool IsWidgetInStack(UUserWidget* Widget) override;

	bool IsIgnoredInputKey(FKey Key) override;

	void OnKeyPressed(FKey Key) override;

protected:
	virtual void Internal_AddWidgetToViewport(UUserWidget* Widget) PURE_VIRTUAL(UBaseuiSystemComponent::Internal_AddWidgetToViewport, );

private:
	void Internal_RemoveWidgetFromViewport(UUserWidget* WidgetToRemove, bool IsTopLayer);

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

	// will always be the lowest layer. all widgets will be added and removed from the canvas here
	UUserWidget* HudLayer;
};
