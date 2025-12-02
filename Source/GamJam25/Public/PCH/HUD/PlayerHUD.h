// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PlayerHUD.generated.h"

class UBorder;
class UTextBlock;
class UProgressBar;
/**
 * 
 */
UCLASS(Abstract,Blueprintable)//prevents using the cpp file and allows blueprint inheritance
//abstract means this class can't be instantiated directly, it can only be used as a parent
class GAMJAM25_API UPlayerHUD : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION()
	void OnHealthChanged(float NewHealth);

	UFUNCTION()
	void OnScoreChanged(uint8 NewScore);

	UFUNCTION()
	void SetMaxHealth(float PlayerMaxHealth);
	
	UFUNCTION()
	void OnWin(bool won = false);
	
	UFUNCTION()
	void OnDeath(bool died = false);

protected:
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UProgressBar>HealthBar;

	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UTextBlock>ScoreText;
	
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UBorder>WinBox;
	
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UBorder>DeathBox;

	float MaxHealth= 100.0f;

	FText ScoreLabel = FText::FromString("Score: {0}");
};
