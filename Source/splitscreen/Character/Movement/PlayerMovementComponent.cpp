// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerMovementComponent.h"
#include "GameFramework/Character.h"
#include "PlayerMovementPrimaryDataAsset.h"

void UPlayerMovementComponent::ReceiveMoveInput(FVector2D MoveInput) {
	NO_CHARACTER_REF_ERROR_CHECK

	FVector ForwardVector = GetOwner()->GetActorForwardVector();
	FVector RightVector = GetOwner()->GetActorRightVector();
	CurrMoveVector = (MoveInput.X * RightVector + MoveInput.Y * ForwardVector) * MoveSpeed;
	CurrMoveVector.Normalize();
	this->CharacterRef->AddMovementInput(CurrMoveVector);
}

void UPlayerMovementComponent::BeginPlay() {
	Super::BeginPlay();

	CHECK_POINTER_IF_NULL_LOG_ERRROR_AND_RETURN_VOID(this->PlayerMovementDataAsset, *(this->GetName()), TEXT("Player movement data asset missing"))

	// variable initialisation
	this->MoveSpeed = this->PlayerMovementDataAsset->PlayerMovementSpeed;
}
