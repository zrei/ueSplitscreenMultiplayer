// Fill out your copyright notice in the Description page of Project Settings.


#include "BasePlayerController.h"
#include "Input/InputControllerComponent.h"

ABasePlayerController::ABasePlayerController() {
	this->ComponentLedger = this->CreateDefaultSubobject<UComponentLedger>(TEXT("Component Ledger"));
	this->InputController = this->CreateDefaultSubobject<UInputControllerComponent>(TEXT("Input Controller"));
}

UComponentLedger* ABasePlayerController::GetComponentLedger() {
	return this->ComponentLedger;
}
