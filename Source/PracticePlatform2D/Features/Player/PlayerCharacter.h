// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperCharacter.h"
#include "InputMappingContext.h"
#include "PaperFlipbook.h"
#include "PaperFlipbookComponent.h"
#include "PlayerCharacter.generated.h"

/**
 *
 */
UCLASS()
class PRACTICEPLATFORM2D_API APlayerCharacter : public APaperCharacter
{
	GENERATED_BODY()

public:
	APlayerCharacter();

protected:
	virtual void BeginPlay() override;

	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

	virtual void Landed(const FHitResult& Hit) override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Input")
	UInputMappingContext* ImcDefault;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Input")
	UInputAction* IaMove;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input")
	UInputAction* IaJump;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Sprite")
	UPaperFlipbook* PfIdle;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Sprite")
	UPaperFlipbook* PfRun;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Sprite")
	UPaperFlipbook* PfJump;

	void OnMoveInput(const FInputActionValue& Value);

	void OnMoveCompleted(const FInputActionValue& Value);

	void OnJumpInput(const FInputActionValue& Value);
};