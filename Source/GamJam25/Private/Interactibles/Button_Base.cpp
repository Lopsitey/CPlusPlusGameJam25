// Fill out your copyright notice in the Description page of Project Settings.


#include "Interactibles/Button_Base.h"

#include "GamJam25/Managers/TurretWorldManager.h"
#include "Kismet/KismetSystemLibrary.h"
#include "PCH/PCH_Interface.h"


// Sets default values
AButton_Base::AButton_Base()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BoxCollision = CreateDefaultSubobject<UBoxComponent>("Collider");
	RootComponent = BoxCollision;
	SetRootComponent(BoxCollision);

	BaseMesh=CreateDefaultSubobject<UStaticMeshComponent>("BaseMesh");
	BaseMesh->SetupAttachment(BoxCollision);
}

// Called when the game starts or when spawned
void AButton_Base::BeginPlay()
{
	Super::BeginPlay();
	
}

void AButton_Base::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	if (BoxCollision)
	{
		BoxCollision->OnComponentBeginOverlap.RemoveDynamic(this, &AButton_Base::ButtonOverlapped);
		BoxCollision->OnComponentBeginOverlap.AddDynamic(this, &AButton_Base::ButtonOverlapped);
		
		BoxCollision->OnComponentEndOverlap.RemoveDynamic(this, &AButton_Base::ButtonOverlapEnd);
		BoxCollision->OnComponentEndOverlap.AddDynamic(this, &AButton_Base::ButtonOverlapEnd);
	}
}

// Called every frame
void AButton_Base::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AButton_Base::Interact_Implementation()
{
	IInteractionInterface::Interact_Implementation();
	if (!bInteracted)
	{
		if (UWorld* World = GetWorld())
		{
			if (UTurretWorldManager* Manager = World->GetSubsystem<UTurretWorldManager>())
			{
				Manager->DisableAllTurrets();
				bInteracted = true;
			}
			GEngine->AddOnScreenDebugMessage(-1,2.0f,FColor::Red, TEXT("Turrets Disabled"));
		}
	}
	else
	{
		if (UWorld* World = GetWorld())
		{
			if (UTurretWorldManager* Manager = World->GetSubsystem<UTurretWorldManager>())
			{
				Manager->EnableAllTurrets();
				bInteracted = false;
				
			}
			GEngine->AddOnScreenDebugMessage(-1,2.0f,FColor::Green, TEXT("Turrets Enabled"));
		}
	}
}

void AButton_Base::ButtonOverlapped(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (UKismetSystemLibrary::DoesImplementInterface(OtherActor,UPCH_Interface::StaticClass()))
	{
		IPCH_Interface::Execute_SetOverlappedActor(OtherActor,this);
		Interact_Implementation();
	}
}

void AButton_Base::ButtonOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (UKismetSystemLibrary::DoesImplementInterface(OtherActor,UPCH_Interface::StaticClass()))
	{
		IPCH_Interface::Execute_SetOverlappedActor(OtherActor,nullptr);
	}
}

