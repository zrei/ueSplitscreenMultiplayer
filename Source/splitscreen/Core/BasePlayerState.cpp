// Fill out your copyright notice in the Description page of Project Settings.


#include "BasePlayerState.h"

ABasePlayerState::ABasePlayerState() {
	this->ComponentLedger = this->CreateDefaultSubobject<UComponentLedger>(TEXT("Component Ledger"));
}

UComponentLedger* ABasePlayerState::GetComponentLedger() {
	return this->ComponentLedger;
}