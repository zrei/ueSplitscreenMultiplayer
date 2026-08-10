// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Core/BaseActorComponent.h"
#include "ComponentLedger.generated.h"

/**
 * 
 */
UCLASS()
class SPLITSCREEN_API UComponentLedger : public UBaseActorComponent
{
	GENERATED_BODY()

private:
	TMap<const FName, UActorComponent*> NameComponentLedger{};
	TMap<const TSubclassOf<UInterface>, UActorComponent*> InterfaceComponentLedger{};
	TMap<const TSubclassOf<UActorComponent>, UActorComponent*> ClassComponentLedger{};

	UActorComponent* GetComponentByName(const FName& ComponentName);
	UActorComponent* GetComponentByClass(const TSubclassOf<UActorComponent> ComponentClass);
	UActorComponent* GetComponentByInterface(const TSubclassOf<UInterface> ComponentInterface);

public:
	bool TryGetComponentByName(const FName& ComponentName, UActorComponent* ComponentPtr);
	bool TryGetComponentByClass(const TSubclassOf<UActorComponent> ComponentClass, UActorComponent* ComponentPtr);
	bool TryGetComponentByInterface(const TSubclassOf<UInterface> ComponentInterface, UActorComponent* ComponentPtr);
};
