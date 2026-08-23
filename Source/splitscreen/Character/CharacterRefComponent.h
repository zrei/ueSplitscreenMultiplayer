// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Core/BaseActorComponent.h"
#include "Common/Macros/ErrorMacros.h"
#include "CharacterRefComponent.generated.h"

#define NO_CHARACTER_REF_ERROR_CHECK CHECK_POINTER_IF_NULL_LOG_ERRROR_AND_RETURN_VOID(this->CharacterRef, *(this->GetName()), TEXT("No character ref found"))

/**
 * 
 */
UCLASS()
class SPLITSCREEN_API UCharacterRefComponent : public UBaseActorComponent
{
	GENERATED_BODY()

protected:
	TObjectPtr<ACharacter> CharacterRef;

public:
	virtual void BeginPlay() override;
};
