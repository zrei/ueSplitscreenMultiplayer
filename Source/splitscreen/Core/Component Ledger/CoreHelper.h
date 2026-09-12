// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "CoreInterface.h"
#include "CoreHelper.generated.h"

/**
 * 
 */
UCLASS()
class SPLITSCREEN_API UCoreHelper : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	template <typename T>
	static bool GetInterfaceComponentFromUObject(UObject* Obj, TSubclassOf<UInterface> InterfaceType, T* InterfacePtr) {
		if (Obj && Obj->Implements<UCoreInterface>()) {
			UActorComponent* ActorComponent = NULL;
			if (Cast<ICoreInterface>(Obj)->TryGetComponentFromLedgerByInterface(InterfaceType, ActorComponent)) {
				InterfacePtr = Cast<T>(ActorComponent);
				return InterfacePtr != NULL;
			}
		}
		
		return false;
	}
};
