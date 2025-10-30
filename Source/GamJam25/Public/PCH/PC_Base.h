﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "InputMappingContext.h"
#include "PC_Base.generated.h"

class UIADataConfig;
/**
 * 
 */
UCLASS()
class GAMJAM25_API APC_Base : public APlayerController
{
	GENERATED_BODY()
	
protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Input)
	TObjectPtr<UInputMappingContext>MappingContext;

	UPROPERTY()
	TObjectPtr<AActor> LocalPCH;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Input)
	TObjectPtr<UIADataConfig> InputActions;

	void Move(const FInputActionInstance& Instance);
	void Look(const FInputActionInstance& Instance);
	void Jump(const FInputActionInstance& Instance);
	void Action(const FInputActionInstance& Instance);
	void Fire(const FInputActionInstance& Instance);
	void Scroll(const FInputActionInstance& Instance);

private:
	UFUNCTION()
	void UpdateScore(uint8 score);
	
	UFUNCTION()
	void GameWin();
};
