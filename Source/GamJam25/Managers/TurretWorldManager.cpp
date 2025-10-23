// Fill out your copyright notice in the Description page of Project Settings.


#include "TurretWorldManager.h"

#include "Enemies/Turret_Base.h"

void UTurretWorldManager::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
}

void UTurretWorldManager::Deinitialize()
{
	RegisteredTurrets.Empty();
	Super::Deinitialize();
}

void UTurretWorldManager::RegisterTurret(ATurret_Base* TurretActor)
{
	if (TurretActor && !RegisteredTurrets.Contains(TurretActor))//adds the turret if it isn't already in the array
		RegisteredTurrets.Add(TurretActor);
}

void UTurretWorldManager::UnregisterTurret(ATurret_Base* TurretActor)
{
	if (TurretActor)
		RegisteredTurrets.Remove(TurretActor);
}

void UTurretWorldManager::DisableAllTurrets()
{
	for (auto& TurretWeakPtr:RegisteredTurrets)
	{
		if (ATurret_Base* TurretActor = TurretWeakPtr.Get())
		{
			TurretActor->SetTurretEnabled(false);
		}
	}
	UE_LOG(LogTemp,Log,TEXT("All turrets disabled"));
}

void UTurretWorldManager::EnableAllTurrets()
{
	for (auto& TurretWeakPtr:RegisteredTurrets)
	{
		if (ATurret_Base* TurretActor = TurretWeakPtr.Get())
		{
			TurretActor->SetTurretEnabled(true);
		}
	}
	UE_LOG(LogTemp,Log,TEXT("All turrets enabled"));
}