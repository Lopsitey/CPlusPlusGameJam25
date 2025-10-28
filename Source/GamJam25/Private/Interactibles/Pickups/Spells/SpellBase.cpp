// Fill out your copyright notice in the Description page of Project Settings.


#include "Interactibles/Pickups/Spells/SpellBase.h"


// Sets default values
ASpellBase::ASpellBase()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

void ASpellBase::SpellCast_Implementation()
{
}

void ASpellBase::AltSpellCast_Implementation()
{
}

void ASpellBase::Charge_Implementation()
{
	uint8 ToReload = FMath::Clamp(CurrentReserve-(MaxAmmo-CurrentAmmo),0,MaxAmmo); 

	CurrentAmmo += ToReload;
	CurrentReserve -= ToReload;
}

// Called when the game starts or when spawned
void ASpellBase::BeginPlay()
{
	Super::BeginPlay();

	CurrentAmmo = MaxAmmo;
	CurrentReserve = MaxReserve;
}

void ASpellBase::SpawnProjectile_Implementation()
{
}

void ASpellBase::ModifyAmmo_Implementation(uint8 ToReduce)
{
	CurrentAmmo = FMath::Clamp(CurrentAmmo - ToReduce,0,MaxAmmo);
}

bool ASpellBase::HasAmmo()
{
	return CurrentAmmo > 0;
}

void ASpellBase::HandleEmpty_Implementation()
{
	if (bAllowedAutoReload)
	{
		Charge();
	}
	else
	{
		//TODO - reload anim or SFX / VFX 
	}
}

// Called every frame
void ASpellBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

