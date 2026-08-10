// Fill out your copyright notice in the Description page of Project Settings.


#include "BasePlayerController.h"

ABasePlayerController::ABasePlayerController() {
	this->ComponentLedger = this->CreateDefaultSubobject<UComponentLedger>(TEXT("Component Ledger"));
}

UComponentLedger* ABasePlayerController::GetComponentLedger() {
	return this->ComponentLedger;
}