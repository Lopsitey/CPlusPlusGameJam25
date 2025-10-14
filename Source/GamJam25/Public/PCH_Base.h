// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PCH/Inputs/IA_Interface.h"
#include "PCH_Base.generated.h"

class UCameraComponent;
class USpringArmComponent;

UCLASS()
class GAMJAM25_API APCH_Base : public ACharacter, public IIA_Interface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APCH_Base();
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void Move_Implementation(const FInputActionInstance& Instance) override;
	virtual void JumpAction_Implementation(const FInputActionInstance& Instance) override;
	virtual void Action_Implementation(const FInputActionInstance& Instance) override;
	virtual void Look_Implementation(const FInputActionInstance& Instance) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USpringArmComponent> SpringArm;

	UPROPERTY(VisibleAnywhere);
	TObjectPtr<UCameraComponent> Camera;

	UPROPERTY(BlueprintReadWrite, Category= Speeds);
	float WalkSpeed= 400.0f;
	
};
