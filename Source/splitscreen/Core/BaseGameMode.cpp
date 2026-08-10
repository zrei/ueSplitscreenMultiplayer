// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseGameMode.h"

ABaseGameMode::ABaseGameMode() {
	this->ComponentLedger = this->CreateDefaultSubobject<UComponentLedger>(TEXT("Component Ledger"));
}

UComponentLedger* ABaseGameMode::GetComponentLedger() {
	return this->ComponentLedger;
}