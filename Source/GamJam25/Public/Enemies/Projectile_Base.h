// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Projectile_Base.generated.h"

class USphereComponent;
class UProjectileMovementComponent;

UCLASS()
class GAMJAM25_API AProjectile_Base : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AProjectile_Base();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USphereComponent> SphereComponent;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UStaticMeshComponent> StaticMeshComponent;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UProjectileMovementComponent> ProjectileMovementComponent;

	UPROPERTY(EditDefaultsOnly, Category="Damage")
	float BaseDamage = 50.0f;

	UFUNCTION()
	void ProjectileHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
					   FVector NormalImpulse, const FHitResult& Hit);
};
