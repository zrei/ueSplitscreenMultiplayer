// Fill out your copyright notice in the Description page of Project Settings.


#include "ComponentLedger.h"

UActorComponent* UComponentLedger::GetComponentByClass(const TSubclassOf<UActorComponent> ComponentClass) {
	if (this->ClassComponentLedger.Contains(ComponentClass))
		return this->ClassComponentLedger[ComponentClass];

	UActorComponent* FoundActorComponent = this->GetOwner()->FindComponentByClass(ComponentClass);

	if (FoundActorComponent)
		this->ClassComponentLedger.Add(ComponentClass, FoundActorComponent);

	return FoundActorComponent;
}

bool UComponentLedger::TryGetComponentByClass(const TSubclassOf<UActorComponent> ComponentClass, UActorComponent* ComponentPtr) {
	ComponentPtr = this->GetComponentByClass(ComponentClass);
	return ComponentPtr != NULL;
}

UActorComponent* UComponentLedger::GetComponentByInterface(TSubclassOf<UInterface> ComponentInterface) {
	if (this->InterfaceComponentLedger.Contains(ComponentInterface))
		return this->InterfaceComponentLedger[ComponentInterface];

	UActorComponent* FoundActorComponent = this->GetOwner()->FindComponentByInterface(ComponentInterface);

	if (FoundActorComponent)
		this->InterfaceComponentLedger.Add(ComponentInterface, FoundActorComponent);

	return FoundActorComponent;
}

bool UComponentLedger::TryGetComponentByInterface(const TSubclassOf<UInterface> ComponentInterface, UActorComponent* ComponentPtr) {
	ComponentPtr = this->GetComponentByInterface(ComponentInterface);
	return ComponentPtr != NULL;
}

UActorComponent* UComponentLedger::GetComponentByName(const FName& ComponentName) {
	if (this->NameComponentLedger.Contains(ComponentName))
		return this->NameComponentLedger[ComponentName];

	UActorComponent* FoundActorComponent = this->GetOwner()->FindComponentByTag<UActorComponent>(ComponentName);

	if (FoundActorComponent)
		this->NameComponentLedger.Add(ComponentName, FoundActorComponent);

	return FoundActorComponent;
}

bool UComponentLedger::TryGetComponentByName(const FName& ComponentName, UActorComponent* ComponentPtr) {
	ComponentPtr = this->GetComponentByName(ComponentName);
	return ComponentPtr != NULL;
}