// Fill out your copyright notice in the Description page of Project Settings.

#include "BasePlayerCharacter.h"
#include "EnhancedInputComponent.h"
#include "../Common/Logger.h"

// Sets default values
ABasePlayerCharacter::ABasePlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ABasePlayerCharacter::BeginPlay()
{
	Super::BeginPlay();	
}

// Called every frame
void ABasePlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void ABasePlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent);
	EnhancedInputComponent->BindAction(MoveInputAction, ETriggerEvent::Triggered, this, &ABasePlayerCharacter::MoveAction);
	EnhancedInputComponent->BindAction(LookInputAction, ETriggerEvent::Triggered, this, &ABasePlayerCharacter::LookAction);
}

void ABasePlayerCharacter::LookAction(const FInputActionValue& LookValue)
{
	CurrLookInput = LookValue.Get<FVector2D>();
	AddControllerYawInput(CurrLookInput.X * LookSpeed);
	AddControllerPitchInput(CurrLookInput.Y * LookSpeed);
	OnLookAction(CurrLookInput);
}

void ABasePlayerCharacter::MoveAction(const FInputActionValue& MoveValue)
{
	CurrMoveInput = MoveValue.Get<FVector2D>();
	FVector ForwardVector = GetActorForwardVector();
	FVector RightVector = GetActorRightVector();
	CurrMoveVector = (CurrMoveInput.X * RightVector + CurrMoveInput.Y * ForwardVector) * MoveSpeed;
	CurrMoveVector.Normalize();
	AddMovementInput(CurrMoveVector);
	OnMoveAction(CurrMoveInput, CurrMoveVector);
}
