// Fill out your copyright notice in the Description page of Project Settings.

#include "GameFramework/GameStateBase.h"
#include "Kismet/GameplayStatics.h"
#include "UI/BPFL_UI.h"
#include "UI/UiSystemInterface.h"
#include "Core/Component Ledger/CoreHelper.h"
#include "Common/Logger.h"

void UBPFL_UI::OpenUiInFullscreenViewport(const UObject* WorldContext, UUserWidget* Widget, bool HideOthers) {
	IUiSystemInterface* UiController = GetUiControllerPointer(WorldContext);
	if (!UiController) {
		return;
	}

	UiController->AddWidgetToViewport(Widget, HideOthers);
}

bool UBPFL_UI::RemoveUiFromFullscreenViewport(const UObject* WorldContext, UUserWidget* Widget) {
	IUiSystemInterface* UiController = GetUiControllerPointer(WorldContext);
	if (UiController && UiController->RemoveWidgetFromViewport(Widget)) {
		return true;
	}

	return false;
}

bool UBPFL_UI::PopTopWidgetFromFullscreenViewport(const UObject* WorldContext) {
	IUiSystemInterface* UiController = GetUiControllerPointer(WorldContext);
	if (UiController && UiController->PopTopWidgetFromViewport()) {
		return true;
	}

	return false;
}

bool UBPFL_UI::IsFullscreenWidgetStackEmpty(const UObject* WorldContext) {
	IUiSystemInterface* UiController = GetUiControllerPointer(WorldContext);
	if (!UiController) {
		return false;
	}

	return UiController->IsUiStackEmpty();
}

bool UBPFL_UI::IsWidgetInFullscreenStack(const UObject* WorldContext, UUserWidget* Widget) {
	IUiSystemInterface* UiController = GetUiControllerPointer(WorldContext);
	if (!UiController) {
		return false;
	}

	return UiController->IsWidgetInStack(Widget);
}

IUiSystemInterface* UBPFL_UI::GetUiControllerPointer(const UObject* WorldContext) {
	AGameStateBase* GameState = UGameplayStatics::GetGameState(WorldContext->GetWorld());
	IUiSystemInterface* UiController = NULL;
	if (GameState && UCoreHelper::GetInterfaceComponentFromUObject(GameState, UUiSystemInterface::StaticClass(), UiController)) {
		return UiController;
	}

	ULogger::LogErrorToScreen("Cannot find Ui controller");
	return NULL;
}