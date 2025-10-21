// Fill out your copyright notice in the Description page of Project Settings.


#include "TurretWorldManager.h"

#include "Enemies/Turret_Base.h"

void UTurretWorldManager::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	UE_LOG(LogTemp, Warning, TEXT("TurretWorldManager::Initialize"));
}

void UTurretWorldManager::Deinitialize()
{
	RegisteredTurrets.Empty();
	Super::Deinitialize();
	UE_LOG(LogTemp, Warning, TEXT("TurretWorldManager::Deinitialize"));
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
}
