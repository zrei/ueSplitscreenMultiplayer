// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseGameState.h"
#include "Multiplayer/SplitscreenController.h"
#include "Multiplayer/SplitscreenControllerInterface.h"
#include "Common/Logger.h"

ABaseGameState::ABaseGameState() {
	this->ComponentLedger = this->CreateDefaultSubobject<UComponentLedger>(TEXT("Component Ledger"));
	this->SplitscreenControllerComponent = this->CreateDefaultSubobject<USplitscreenController>(TEXT("Splitscreen Controller"));
}

UComponentLedger* ABaseGameState::GetComponentLedger() {
	return this->ComponentLedger;
}
