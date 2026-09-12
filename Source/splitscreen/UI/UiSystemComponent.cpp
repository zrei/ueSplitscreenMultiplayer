// Fill out your copyright notice in the Description page of Project Settings.


#include "UiSystemComponent.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/GameStateBase.h"
#include "Core/Component Ledger/CoreInterface.h"
#include "Input/InputControllerInterface.h"
#include "Core/Component Ledger/CoreHelper.h"

void UUiSystemComponent::AddWidgetToEntireViewport(UUserWidget* Widget) {
	Widget->AddToViewport();

	AGameStateBase* GameState = UGameplayStatics::GetGameState(GetWorld());
	IInputControllerInterface* InputController = NULL;
	if (GameState && UCoreHelper::GetInterfaceComponentFromUObject(GameState, UInputControllerInterface::StaticClass(), InputController)) {
		InputController->SwitchToUIInput(Widget, EMouseLockMode::DoNotLock);
	}
}

void UUiSystemComponent::AddWidgetToLocalPlayerScreen(UUserWidget* Widget, ULocalPlayer* LocalPlayer) {

}

void UUiSystemComponent::RemoveWidgetFromEntireViewport(UUserWidget* Widget) {

}

void UUiSystemComponent::RemoveWidgetFromLocalPlayerScreen(UUserWidget* Widget, ULocalPlayer* LocalPlayer) {

}