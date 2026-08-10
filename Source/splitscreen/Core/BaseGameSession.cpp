// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseGameSession.h"

ABaseGameSession::ABaseGameSession() {
	this->ComponentLedger = this->CreateDefaultSubobject<UComponentLedger>(TEXT("Component Ledger"));
}

UComponentLedger* ABaseGameSession::GetComponentLedger() {
	return this->ComponentLedger;
}