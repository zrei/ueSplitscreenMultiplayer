// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseGameState.h"
#include "Common/Logger.h"
#include "Game/GameStateStoreComponent.h"

ABaseGameState::ABaseGameState() {
	this->ComponentLedger = this->CreateDefaultSubobject<UComponentLedger>(TEXT("Component Ledger"));
	this->GameStateStore = this->CreateDefaultSubobject<UGameStateStoreComponent>(TEXT("Game State Store"));
}

UComponentLedger* ABaseGameState::GetComponentLedger() {
	return this->ComponentLedger;
}
