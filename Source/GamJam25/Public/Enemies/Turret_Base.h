// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "NiagaraSystem.h"
#include "Turret_Base.generated.h"

class AProjectile_Base;
class UArrowComponent;

UCLASS()
class GAMJAM25_API ATurret_Base : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ATurret_Base();
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UStaticMeshComponent> BaseMesh;
	
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UStaticMeshComponent> BarrelMesh;
	
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UArrowComponent> FirePoint;
	
	UPROPERTY(EditDefaultsOnly, Category="TurretData")
	float FireSpeed = 0.5f;

	UPROPERTY(EditDefaultsOnly, Category="TurretData")
	FTimerHandle FireTimer;

	UPROPERTY(EditDefaultsOnly, Category="TurretData")
	TSubclassOf<AProjectile_Base> ProjectileClass;

	UPROPERTY(EditDefaultsOnly, Category="TurretData")
	TObjectPtr<USoundBase> FireSound;

	UPROPERTY(EditDefaultsOnly, Category="TurretData")
	float FireAudioVolume = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="TurretData")
	TObjectPtr<UNiagaraSystem> FireFx;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="TurretData")
	void Fire();

	UFUNCTION(BlueprintCallable, Category = "TurretData")
	void SetTurretEnabled(bool bEnabled);

private:
	bool bTurretIsEnabled = true;
};
