// Fill out your copyright notice in the Description page of Project Settings.


#include "Interactibles/Pickups/PickupBase.h"

#include "Components/SphereComponent.h"
#include "Interactibles/Pickups/Spells/PickupDataAsset.h"
#include "Kismet/GameplayStatics.h"


// Sets default values
APickupBase::APickupBase()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Collider = CreateDefaultSubobject<USphereComponent>("Collider");
	SetRootComponent(Collider);

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>("BaseMesh");
	BaseMesh->SetupAttachment(Collider);

	Collider->OnComponentBeginOverlap.AddUniqueDynamic(this, &APickupBase::OnBeginOverlap);
}

// Called when the game starts or when spawned
void APickupBase::BeginPlay()
{
	Super::BeginPlay();
	
}

void APickupBase::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

	if (PickupDA)
	{
		if (PickupDA->PickupMesh)
		{
			BaseMesh->SetStaticMesh(PickupDA->PickupMesh);
		}
	}
}

void APickupBase::OnPickedUp_Implementation(AActor* PickingActor)
{
	
}

void APickupBase::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->ActorHasTag("Player"))
	{
		OnPickedUp(OtherActor);
		if (PickupDA && PickupDA->PickupSound)
			UGameplayStatics::PlaySoundAtLocation(GetWorld(), PickupDA->PickupSound, GetActorLocation());

		Destroy();
		
	}
}

// Called every frame
void APickupBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

