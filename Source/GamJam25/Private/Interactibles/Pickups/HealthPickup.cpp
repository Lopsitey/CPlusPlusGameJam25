// Fill out your copyright notice in the Description page of Project Settings.


#include "Interactibles/Pickups/HealthPickup.h"

#include "Interactibles/Pickups/Spells/PickupDataAsset.h"
#include "Kismet/KismetSystemLibrary.h"
#include "PCH/PCH_Interface.h"


// Sets default values
AHealthPickup::AHealthPickup()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AHealthPickup::BeginPlay()
{
	Super::BeginPlay();
	
}

void AHealthPickup::OnPickedUp_Implementation(AActor* PickingActor)
{
	Super::OnPickedUp_Implementation(PickingActor);

	if (!PickupDA)
		return;

	float HealthCValue = PickupDA->PickupValue;

	if (UKismetSystemLibrary::DoesImplementInterface(PickingActor, UPCH_Interface::StaticClass()))
		IPCH_Interface::Execute_AddHealthFromPickup(PickingActor, HealthCValue);
}

// Called every frame
void AHealthPickup::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

