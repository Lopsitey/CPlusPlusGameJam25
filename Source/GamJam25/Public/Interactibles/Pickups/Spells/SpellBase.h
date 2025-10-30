// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SpellBase.generated.h"

class AProjectile_Base;//forward declared for use in the projectile class below

UCLASS(Abstract)//never needs to be used directly - should always be instantiated
class GAMJAM25_API ASpellBase : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ASpellBase();

	UFUNCTION(BlueprintNativeEvent,BlueprintCallable, Category="Spell Base Data")
	void SpellCast();

	UFUNCTION(BlueprintNativeEvent,BlueprintCallable, Category="Spell Base Data")
	void AltSpellCast();

	UFUNCTION(BlueprintNativeEvent,BlueprintCallable, Category="Spell Base Data")
	void Charge();//reload
	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadWrite, Category="Spell Base Data")
	uint8 CurrentAmmo = 0;

	UPROPERTY(BlueprintReadWrite, Category="Spell Base Data")
	uint8 CurrentReserve;//spell magazine

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Spell Base Data")
	uint8 MaxAmmo;

	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly, Category="Spell Base Data")
	uint8 MaxReserve;

	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly, Category="Spell Base Data")
	bool bAllowedAutoReload = true;//if the spells automatically reload

	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly, Category="Spell Base Data")
	TSubclassOf<AProjectile_Base> ProjectileClass;

	UFUNCTION(BlueprintNativeEvent,BlueprintCallable, Category="Spell Base Data")
	void SpawnProjectile();

	UFUNCTION(BlueprintNativeEvent,BlueprintCallable, Category="Spell Base Data")
	void ModifyAmmo(uint8 ToReduce);

	UFUNCTION(BlueprintCallable, Category="Spell Base Data")
	bool HasAmmo();//returns remaining ammunition

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="Spell Base Data")
	void HandleEmpty();
public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
