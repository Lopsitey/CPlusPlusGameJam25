// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interactibles/Pickups/CollectibleBase.h"
#include "Subsystems/WorldSubsystem.h"
#include "CollectiblesManager.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnCollectionEvent);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAllCollectiblesRegistered,uint8, INumOfCollectibles);

/**
 * 
 */
UCLASS()
class GAMJAM25_API UCollectiblesManager : public UWorldSubsystem
{
	GENERATED_BODY()

public:
	
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;

	UPROPERTY(BlueprintAssignable)
	FOnCollectionEvent OnCollectionEvent;
	UPROPERTY(BlueprintAssignable)
	FOnAllCollectiblesRegistered OnAllCollectiblesRegistered;
	
	void NotifyCollection(ACollectibleBase* Collectible);
	void RegisterCollectible(ACollectibleBase* Collectible);
	void FinaliseRegistration();

private:
	UPROPERTY()
	TArray<TWeakObjectPtr<ACollectibleBase>> Collectibles;

	bool bRegistrationComplete = false;
};
