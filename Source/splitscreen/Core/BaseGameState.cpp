// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseGameState.h"
#include "Common/Logger.h"

ABaseGameState::ABaseGameState() {
	this->ComponentLedger = this->CreateDefaultSubobject<UComponentLedger>(TEXT("Component Ledger"));
}

UComponentLedger* ABaseGameState::GetComponentLedger() {
	return this->ComponentLedger;
}
