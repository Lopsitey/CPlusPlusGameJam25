// Fill out your copyright notice in the Description page of Project Settings.


#include "PCH/HUD/PlayerHUD.h"

#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"

void UPlayerHUD::OnHealthChanged(float NewHealth)
{
	if (HealthBar)
		HealthBar->SetPercent(NewHealth/MaxHealth);
}

void UPlayerHUD::OnScoreChanged(uint8 NewScore)
{//formats the text using the curly braces as a placeholder for the score number
	if (ScoreText)
	{
		FText Formatted = FText::Format(ScoreLabel, FText::AsNumber(NewScore));
		ScoreText->SetText(Formatted);
	}
}

void UPlayerHUD::SetMaxHealth(float PlayerMaxHealth)
{
	MaxHealth = PlayerMaxHealth;
}