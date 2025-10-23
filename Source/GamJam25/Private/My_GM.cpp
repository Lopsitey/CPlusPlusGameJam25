// Fill out your copyright notice in the Description page of Project Settings.


#include "GamJam25/Public/My_GM.h"

#include "AI/NavigationSystemBase.h"
#include "Managers/CollectiblesManager.h"

AMy_GM::AMy_GM()
{
}

void AMy_GM::BeginPlay()
{
	Super::BeginPlay();

	if (GetWorld())
	{
		UCollectiblesManager* CoinManager = GetWorld()->GetSubsystem<UCollectiblesManager>();
		CoinManager->OnAllCollectiblesRegistered.AddUniqueDynamic(this, &AMy_GM::SetNumOfCoinsRequired);
        CoinManager->OnCollectionEvent.AddUniqueDynamic(this, &AMy_GM::LogCollectible);
	}
}

void AMy_GM::SetNumOfCoinsRequired(uint8 MaxCoins)
{
	NumberOfRequiredCollectibles=MaxCoins;
}

void AMy_GM::LogCollectible()
{
	++CurrentNumOfCoins;
	
	if (OnUpdateCollectibles.IsBound())
		OnUpdateCollectibles.Broadcast(CurrentNumOfCoins);

	if (CurrentNumOfCoins==NumberOfRequiredCollectibles)
	{
		if (CollectiblesComplete.IsBound())
			CollectiblesComplete.Broadcast();
	}	
}
