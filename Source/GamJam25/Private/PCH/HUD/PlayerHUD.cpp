#include "PCH/HUD/PlayerHUD.h"

#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"

void UPlayerHUD::OnHealthChanged(float NewHealth)
{
	if (HealthBar)
		HealthBar->SetPercent(NewHealth / MaxHealth);//updates the health bar using the new health and max health as a percentage
}

void UPlayerHUD::OnScoreChanged(uint8 NewScore)
{
	if (ScoreText)
	{//formats the text using the curly braces as a placeholder for the score number
		FText Formatted = FText::Format(ScoreLabel,FText::AsNumber(NewScore));//formats the text with the new score
		ScoreText->SetText(Formatted);//updates the text block with the new score
	}
}

void UPlayerHUD::SetMaxHealth(float PlayerMaxHealth)
{
	MaxHealth = PlayerMaxHealth;//sets the max health for the health bar calculations
}
