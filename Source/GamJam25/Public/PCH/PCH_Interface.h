// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interactibles/Pickups/Spells/SpellBase.h"
#include "UObject/Interface.h"
#include "PCH_Interface.generated.h"

// This class does not need to be modified.
UINTERFACE()
class UPCH_Interface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class GAMJAM25_API IPCH_Interface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
    UFUNCTION(BlueprintCallable,BlueprintNativeEvent)
    void SetOverlappedActor(AActor* OverlappedActor);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void SpellCast();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void EnableSpellCasting(bool bEnableFire);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void AddHealthFromPickup(float val);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void AddSpellFromPickup(TSubclassOf<ASpellBase> Spell);
};
