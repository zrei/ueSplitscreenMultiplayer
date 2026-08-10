// Fill out your copyright notice in the Description page of Project Settings.

#include "BaseActor.h"

// Sets default values
ABaseActor::ABaseActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// does this need to be attached. hrm.
	this->ComponentLedger = this->CreateDefaultSubobject<UComponentLedger>(TEXT("ComponentLedger"));
}

UComponentLedger* ABaseActor::GetComponentLedger() {
	return this->ComponentLedger;
}

// Called when the game starts or when spawned
void ABaseActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABaseActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

