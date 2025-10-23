// Fill out your copyright notice in the Description page of Project Settings.


#include "CollectiblesManager.h"

void UCollectiblesManager::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
}

void UCollectiblesManager::Deinitialize()
{
	Super::Deinitialize();
}

void UCollectiblesManager::NotifyCollection(ACollectibleBase* Collectible)
{
	Collectibles.Remove(Collectible);
	OnCollectionEvent.Broadcast();
}

void UCollectiblesManager::RegisterCollectible(ACollectibleBase* Collectible)
{
	if (Collectible && !Collectibles.Contains(Collectible))
	{
		Collectibles.Add(Collectible);
	}
}

void UCollectiblesManager::FinaliseRegistration()
{
	if (!bRegistrationComplete)
	{
		bRegistrationComplete = true;
		if (OnAllCollectiblesRegistered.IsBound())
			OnAllCollectiblesRegistered.Broadcast(Collectibles.Num());
	}
}
