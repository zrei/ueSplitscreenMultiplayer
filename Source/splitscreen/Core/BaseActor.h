// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Component Ledger/CoreInterface.h"
#include "BaseActor.generated.h"

UCLASS()
class SPLITSCREEN_API ABaseActor : public AActor, public ICoreInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABaseActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere)
	UComponentLedger* ComponentLedger;

	UComponentLedger* GetComponentLedger() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
