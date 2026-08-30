// Fill out your copyright notice in the Description page of Project Settings.


#include "Multiplayer/SplitscreenControllerComponent.h"

void USplitscreenControllerComponent::ToggleSplitscreen(bool ToggleOn) {
	UWorld* World = GEngine->GetWorldFromContextObject(this, EGetWorldErrorMode::LogAndReturnNull);
	if (World)
	{
		UGameViewportClient* GameViewportClient = World->GetGameViewport();
		if (GameViewportClient)
		{
			// already matches config
			if (GameViewportClient->IsSplitscreenForceDisabled() == ToggleOn) {
				return;
			}
			GameViewportClient->SetForceDisableSplitscreen(!ToggleOn);
		}
	}
}