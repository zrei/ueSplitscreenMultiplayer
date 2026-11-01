// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "BPFL_UI.generated.h"

/**
 * 
 */
UCLASS()
class SPLITSCREEN_API UBPFL_UI : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContext"))
	static void OpenUiInViewport(const UObject* WorldContext, UUserWidget* Widget);

	UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContext"))
	static void RemoveUiFromViewport(const UObject* WorldContext, UUserWidget* Widget);
};
