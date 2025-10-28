﻿// Fill out your copyright notice in the Description page of Project Settings.


#include "Interactibles/Pickups/Spells/FireSpell.h"

#include "Components/ArrowComponent.h"
#include "Enemies/Projectile_Base.h"


// Sets default values
AFireSpell::AFireSpell()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	FirePoint = CreateDefaultSubobject<UArrowComponent>("Arrow 1");
	FirePoint2 = CreateDefaultSubobject<UArrowComponent>("Arrow 2");
	FirePoint3 = CreateDefaultSubobject<UArrowComponent>("Arrow 3");

	SetRootComponent(FirePoint);
	FirePoint2->SetupAttachment(FirePoint);
	FirePoint3->SetupAttachment(FirePoint);
	
	FirePoint->SetRelativeLocation(FVector(60,0,0));
	FirePoint2->SetRelativeLocation(FVector(-20,-90,0));
	FirePoint3->SetRelativeLocation(FVector(-20,90,0));

	FirePoint2->SetRelativeRotation(FRotator(0,-15,-90));
	FirePoint3->SetRelativeRotation(FRotator(0,15,-90));
}

// Called when the game starts or when spawned
void AFireSpell::BeginPlay()
{
	Super::BeginPlay();

	GetComponents<UArrowComponent>(FirePoints);	
}

void AFireSpell::SpellCast_Implementation()
{
	Super::SpellCast_Implementation();
	
	if(CurrentAmmo>2)
	{
		for (int i = 0; i<3; ++i)
		{
			ActiveFirePoint=i;
			SpawnProjectile();
		}
	}

	ActiveFirePoint=0;
	ModifyAmmo(3);
}

void AFireSpell::SpawnProjectile_Implementation()
{
	Super::SpawnProjectile_Implementation();

	FVector location = FirePoints[ActiveFirePoint]->GetComponentLocation();
	FRotator rotation = FirePoints[ActiveFirePoint]->GetComponentRotation();
	
	GetWorld()->SpawnActor(ProjectileClass, &location, &rotation);
}

// Called every frame
void AFireSpell::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

