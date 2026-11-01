// Fill out your copyright notice in the Description page of Project Settings.

#include "GameFramework/GameStateBase.h"
#include "Kismet/GameplayStatics.h"
#include "UI/BPFL_UI.h"
#include "UI/UiSystemInterface.h"
#include "Core/Component Ledger/CoreHelper.h"
#include "Common/Logger.h"

void UBPFL_UI::OpenUiInViewport(const UObject* WorldContext, UUserWidget* Widget) {
	AGameStateBase* GameState = UGameplayStatics::GetGameState(WorldContext->GetWorld());
	IUiSystemInterface* UiController = NULL;
	if (GameState && UCoreHelper::GetInterfaceComponentFromUObject(GameState, UUiSystemInterface::StaticClass(), UiController)) {
		UiController->AddWidgetToEntireViewport(Widget);
	}
	else if (!GameState) {
		ULogger::LogErrorToScreen(TEXT("CANNOT FIND GAMESTATE"));
	}
	else {
		ULogger::LogErrorToScreen(TEXT("CANNOT OPEN WIDGET"));
	}
}

void UBPFL_UI::RemoveUiFromViewport(const UObject* WorldContext, UUserWidget* Widget) {
	AGameStateBase* GameState = UGameplayStatics::GetGameState(WorldContext->GetWorld());
	IUiSystemInterface* UiController = NULL;
	if (GameState && UCoreHelper::GetInterfaceComponentFromUObject(GameState, UUiSystemInterface::StaticClass(), UiController)) {
		UiController->RemoveWidgetFromEntireViewport(Widget);
	}
	else {
		ULogger::LogErrorToScreen(TEXT("CANNOT CLOSE WIDGET"));
	}
}