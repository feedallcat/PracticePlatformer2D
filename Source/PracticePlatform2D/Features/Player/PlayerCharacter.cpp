// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerCharacter.h"
#include "EnhancedInputSubsystems.h"
#include "InputMappingContext.h"
#include "EnhancedInputComponent.h"
#include "PaperFlipbookComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/PlayerController.h"

APlayerCharacter::APlayerCharacter() {

}

void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (APlayerController* PlayerController = Cast<APlayerController>(GetController())) {
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer())) {
			if (ImcDefault) {
				Subsystem->AddMappingContext(ImcDefault, 0);
			}
			else {
				UE_LOG(LogTemp, Warning, TEXT("ImcDefault is not set in APlayerCharacter::BeginPlay()"));
			}
		}
	}
}

void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) {
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent)) {
		if (IaMove) {
			EnhancedInputComponent->BindAction(IaMove, ETriggerEvent::Triggered, this, &APlayerCharacter::OnMoveInput);
			EnhancedInputComponent->BindAction(IaMove, ETriggerEvent::Completed, this, &APlayerCharacter::OnMoveCompleted);
		}
		else {
			UE_LOG(LogTemp, Warning, TEXT("IaMove is not set in APlayerCharacter::SetupPlayerInputComponent()"));
		}
		if (IaJump) {
			EnhancedInputComponent->BindAction(IaJump, ETriggerEvent::Started, this, &APlayerCharacter::OnJumpInput);
		}
		else {
			UE_LOG(LogTemp, Warning, TEXT("IaJump is not set in APlayerCharacter::SetupPlayerInputComponent()"));
		}
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("PlayerInputComponent is not of type UEnhancedInputComponent in APlayerCharacter::SetupPlayerInputComponent()"));
	}
}

void APlayerCharacter::Landed(const FHitResult& Hit) {
	Super::Landed(Hit);
	GetSprite()->SetLooping(true);
	GetSprite()->SetFlipbook(PfIdle);
	GetSprite()->Play();
	StopJumping();
}

void APlayerCharacter::OnMoveInput(const FInputActionValue& Value) {
	if (GetCharacterMovement()->IsFalling()) {
		return;
	}
	float value = Value.Get<float>();
	FVector vector = GetActorForwardVector();
	AddMovementInput(vector, value);

	if (GetSprite()->GetFlipbook() != PfJump) {
		GetSprite()->SetFlipbook(PfRun);
		GetSprite()->SetLooping(true);
	}

	if (value >= 0.0f) {
		GetSprite()->SetWorldRotation(FRotator(0.0f, 0.0f, 0.0f));
	}
	else {
		GetSprite()->SetWorldRotation(FRotator(0.0f, -180.0f, 0.0f));
	}
}

void APlayerCharacter::OnMoveCompleted(const FInputActionValue& Value) {
	if (GetCharacterMovement()->IsFalling()) {
		return;
	}
	GetSprite()->SetFlipbook(PfIdle);
}

void APlayerCharacter::OnJumpInput(const FInputActionValue& Value) {
	if (GetCharacterMovement()->IsFalling()) {
		return;
	}
	GetSprite()->SetLooping(false);
	GetSprite()->SetFlipbook(PfJump);
	Jump();
}
