// Fill out your copyright notice in the Description page of Project Settings.


#include "Interactibles/Pickups/CollectibleBase.h"

#include "Components/BoxComponent.h"
#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Managers/CollectiblesManager.h"
#include "PCH/PCH_Interface.h"


// Sets default values
ACollectibleBase::ACollectibleBase()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Collider=CreateDefaultSubobject<USphereComponent>("Collider");
	SetRootComponent(Collider);

	BaseMesh=CreateDefaultSubobject<UStaticMeshComponent>("BaseMesh");
	BaseMesh->SetupAttachment(Collider);
	
	Collider->OnComponentBeginOverlap.AddDynamic(this, &ACollectibleBase::OnOverlapBegin);	
}

// Called when the game starts or when spawned
void ACollectibleBase::BeginPlay()
{
	Super::BeginPlay();
	UCollectiblesManager* Manager = GetWorld()->GetSubsystem<UCollectiblesManager>();
	if (Manager)
	{
		Manager->RegisterCollectible(this);
		FTimerHandle TimerHandle;
		GetWorld()->GetTimerManager().SetTimer(TimerHandle, [this, Manager]()
		{
			Manager->FinaliseRegistration();
		}, 0.1f, false);
	}
	
}

void ACollectibleBase::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (UKismetSystemLibrary::DoesImplementInterface(OtherActor, UPCH_Interface::StaticClass()))
	{
		UCollectiblesManager* Manager = GetWorld()->GetSubsystem<UCollectiblesManager>();
		Manager->NotifyCollection(this);
		if (PickupSound)
			UGameplayStatics::PlaySoundAtLocation(GetWorld(), PickupSound, GetActorLocation());

		Destroy();
	}
}

// Called every frame
void ACollectibleBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

