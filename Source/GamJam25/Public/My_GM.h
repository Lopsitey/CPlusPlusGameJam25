// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "My_GM.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnUpdateCollectibles,uint8, score);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnCollectibleRuleComplete);

UCLASS()
class GAMJAM25_API AMy_GM : public AGameModeBase
{
	GENERATED_BODY()

	AMy_GM();

public:
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite , Category = "GameRules")
	uint8 NumberOfRequiredCollectibles;// The number of collectibles required to complete the game

	UPROPERTY(BlueprintAssignable)
	FOnUpdateCollectibles OnUpdateCollectibles;

	UPROPERTY(BlueprintAssignable)
	FOnCollectibleRuleComplete CollectiblesComplete;

private:
	UFUNCTION()
	void SetNumOfCoinsRequired(uint8 MaxCoins);
	
	UFUNCTION()
	void LogCollectible();
	
	uint8 CurrentNumOfCoins;
};
