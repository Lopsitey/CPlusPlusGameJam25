// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemies/Turret_Base.h"
#include "Enemies/Projectile_Base.h"
#include "Components/ArrowComponent.h"
#include "Kismet/GameplayStatics.h"
#include "NiagaraFunctionLibrary.h"


// Sets default values
ATurret_Base::ATurret_Base()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BaseMesh=CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BaseMesh"));
	SetRootComponent(BaseMesh);

	BarrelMesh=CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BarrelMesh"));
	BarrelMesh->SetupAttachment(BaseMesh);
	BarrelMesh->SetRelativeLocation(FVector(120, 0, 0));
	BarrelMesh->SetRelativeScale3D(FVector(0.5f));

	FirePoint = CreateDefaultSubobject<UArrowComponent>(TEXT("FirePoint"));
	FirePoint->SetupAttachment(BarrelMesh);
	FirePoint->SetRelativeLocation(FVector(280, 0, 0));
}

// Called when the game starts or when spawned
void ATurret_Base::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATurret_Base::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ATurret_Base::Fire_Implementation()
{
	const FVector Location = FirePoint->GetComponentLocation();
	const FRotator Rotation = FirePoint->GetComponentRotation();

	GetWorld()->SpawnActor(ProjectileClass, &Location, &Rotation);

	if (FireSound)
		UGameplayStatics::PlaySound2D(GetWorld(), FireSound, FireAudioVolume);

	if (FireFx)
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, FireFx, Location, Rotation);
}

void ATurret_Base::SetTurretEnabled(bool bEnabled)
{
	bTurretIsEnabled=bEnabled;
	if (!bTurretIsEnabled)
	{
		GetWorldTimerManager().ClearTimer(FireTimer);
	}
	else
	{
		GetWorldTimerManager().SetTimer(FireTimer, this, & ATurret_Base::Fire, FireSpeed, true);
	}
}
