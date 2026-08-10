// Fill out your copyright notice in the Description page of Project Settings.


#include "CoreInterface.h"

bool ICoreInterface::TryGetComponentFromLedgerByClass(const TSubclassOf<UActorComponent> ComponentClass, UActorComponent* ComponentPtr) {
	UComponentLedger* ComponentLedger = this->GetComponentLedger();

	if (!ComponentLedger) {
		ComponentPtr = NULL;
		return false;
	}
	
	return ComponentLedger->TryGetComponentByClass(ComponentClass, ComponentPtr);
}

bool ICoreInterface::TryGetComponentFromLedgerByInterface(const TSubclassOf<UInterface> ComponentInterface, UActorComponent* ComponentPtr) {
	UComponentLedger* ComponentLedger = this->GetComponentLedger();

	if (!ComponentLedger) {
		ComponentPtr = NULL;
		return false;
	}

	return ComponentLedger->TryGetComponentByInterface(ComponentInterface, ComponentPtr);
}

bool ICoreInterface::TryGetComponentFromLedgerByName(const FName& ComponentName, UActorComponent* ComponentPtr) {
	UComponentLedger* ComponentLedger = this->GetComponentLedger();

	if (!ComponentLedger) {
		ComponentPtr = NULL;
		return false;
	}

	return ComponentLedger->TryGetComponentByName(ComponentName, ComponentPtr);
}