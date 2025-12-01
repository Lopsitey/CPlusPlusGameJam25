// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SpellBase.generated.h"

class AProjectile_Base;// you should make things blueprintable if they don't already inherit from AActor - this is just an example usage, but it doesn't actually need it
UCLASS(Abstract, Blueprintable)//Abstract so it can't be directly instantiated 
class GAMJAM25_API ASpellBase : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ASpellBase();
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="Spell Base Data")
	void SpellCast();//Fires the spell
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="Spell Base Data")
	void AltSpellCast();//for the secondary weapon
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="Spell Base Data")
	void Charge();//reload

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	UPROPERTY(BlueprintReadWrite, Category="Spell Base Data")
	uint8 CurrentAmmo = 0;
	
	UPROPERTY(BlueprintReadWrite, Category="Spell Base Data")
	uint8 CurrentReserve = 0;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Spell Base Data")
	uint8 MaxAmmo = 30;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Spell Base Data")
	uint8 MaxReserve = 30;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Spell Base Data")
	bool bAllowedAutoReload = true;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Spell Base Data")
	TSubclassOf<AProjectile_Base> ProjectileClass;
	//can also be TSubclassOf<class AProjectile_Base> ProjectileClass; if I want to inline forward-delcare
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="Spell Base Data")
	void SpawnProjectile();
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="Spell Base Data")
	void ModifyAmmo(uint8 mag);
	
	UFUNCTION(BlueprintNativeEvent, Category="Spell Base Data")
	bool HasAmmo();//returns remaining ammunition
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="Spell Base Data")
	void HandleEmpty();//for reloading

	virtual FTransform GetProjectileTransform();//gets the projectile spawn transform
public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};

inline bool ASpellBase::HasAmmo_Implementation()
{
	return CurrentAmmo>0;
}