// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SphereComponent.h"
#include "GameFramework/Actor.h"
#include "CollectibleBase.generated.h"

UCLASS()
class GAMJAM25_API ACollectibleBase : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ACollectibleBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, Category= CollectibleData)
	TObjectPtr<USphereComponent> Collider;

	UPROPERTY(VisibleAnywhere, Category= CollectibleData)
	TObjectPtr<UStaticMeshComponent> BaseMesh;
	
	UPROPERTY(EditDefaultsOnly, Category= CollectibleData)
	TObjectPtr<USoundBase> PickupSound;

private:
	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
