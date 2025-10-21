//This manager allows everything to be decoupled without direct references between turrets and other systems

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "TurretWorldManager.generated.h"

class ATurret_Base;
/**
 * 
 */
UCLASS()
class GAMJAM25_API UTurretWorldManager : public UWorldSubsystem
{
	GENERATED_BODY()

public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

	virtual void Deinitialize() override;

	void RegisterTurret(ATurret_Base* TurretActor);
	void UnregisterTurret(ATurret_Base* TurretActor);

	UFUNCTION(BlueprintCallable)
	void DisableAllTurrets();
	
private:
	UPROPERTY()
	TArray<TWeakObjectPtr<ATurret_Base>> RegisteredTurrets;
	//an array of pointers which can reference destructible actors
	//Tweak means they can handle the actor being destroyed without having a null / dangling pointer
};
