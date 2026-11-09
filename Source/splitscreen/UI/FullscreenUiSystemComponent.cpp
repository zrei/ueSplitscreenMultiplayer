// Fill out your copyright notice in the Description page of Project Settings.


#include "FullscreenUiSystemComponent.h"
#include "Blueprint/UserWidget.h"

void UFullscreenUiSystemComponent::Internal_AddWidgetToViewport(UUserWidget* Widget) {
	Widget->AddToViewport();
}
