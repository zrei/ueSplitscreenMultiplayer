// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "ComponentLedger.h"
#include "CoreInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UCoreInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class SPLITSCREEN_API ICoreInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual bool TryGetComponentFromLedgerByInterface(const TSubclassOf<UInterface> ComponentInterface, UActorComponent* ComponentPtr); 

	virtual bool TryGetComponentFromLedgerByName(const FName& ComponentName, UActorComponent* ComponentPtr);

	virtual bool TryGetComponentFromLedgerByClass(const TSubclassOf<UActorComponent> ComponentClass, UActorComponent* ComponentPtr);

	virtual UComponentLedger* GetComponentLedger() PURE_VIRTUAL(ICoreInterface::GetComponentLedger, return NULL;);
};
