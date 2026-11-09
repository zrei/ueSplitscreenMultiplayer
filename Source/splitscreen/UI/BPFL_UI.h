// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "BPFL_UI.generated.h"

class UUserWidget;
class AGameStateBase;
class IUiSystemInterface;

/**
 * 
 */
UCLASS()
class SPLITSCREEN_API UBPFL_UI : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContext"))
	static void OpenUiInFullscreenViewport(const UObject* WorldContext, UUserWidget* Widget, bool HideOthers = false);

	UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContext"))
	static bool RemoveUiFromFullscreenViewport(const UObject* WorldContext, UUserWidget* Widget);

	UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContext"))
	static bool PopTopWidgetFromFullscreenViewport(const UObject* WorldContext);

	UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContext"))
	static bool IsFullscreenWidgetStackEmpty(const UObject* WorldContext);

	UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContext"))
	static bool IsWidgetInFullscreenStack(const UObject* WorldContext, UUserWidget* Widget);

private:
	static IUiSystemInterface* GetUiControllerPointer(const UObject* WorldContext);
};
