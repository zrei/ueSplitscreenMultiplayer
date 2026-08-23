// Fill out your copyright notice in the Description page of Project Settings.

#include "CharacterRefComponent.h"
#include "GameFramework/Character.h"

void UCharacterRefComponent::BeginPlay() {
	Super::BeginPlay();

	CharacterRef = (Cast<ACharacter>(GetOwner()));

	NO_CHARACTER_REF_ERROR_CHECK
}
