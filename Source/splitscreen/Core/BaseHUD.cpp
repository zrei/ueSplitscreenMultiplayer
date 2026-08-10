// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseHUD.h"

ABaseHUD::ABaseHUD() {
	this->ComponentLedger = this->CreateDefaultSubobject<UComponentLedger>(TEXT("Component Ledger"));
}

UComponentLedger* ABaseHUD::GetComponentLedger() {
	return this->ComponentLedger;
}