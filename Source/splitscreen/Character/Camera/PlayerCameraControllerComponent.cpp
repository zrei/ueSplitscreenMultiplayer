// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerCameraControllerComponent.h"
#include "GameFramework/Character.h"
#include "PlayerCameraPrimaryDataAsset.h"

void UPlayerCameraControllerComponent::ReceiveLookInput(FVector2D LookInput) {
	NO_CHARACTER_REF_ERROR_CHECK

	this->CharacterRef->AddControllerYawInput(LookInput.X * CameraLookSpeed);
	this->CharacterRef->AddControllerPitchInput(LookInput.Y * CameraLookSpeed);
}

void UPlayerCameraControllerComponent::BeginPlay() {
	Super::BeginPlay();

	CHECK_POINTER_IF_NULL_LOG_ERRROR_AND_RETURN_VOID(this->PlayerCameraDataAsset, *(this->GetName()), TEXT("Player camera data asset missing"))

	// variable initialisation
	this->CameraLookSpeed = this->PlayerCameraDataAsset->CameraLookSpeed;
}