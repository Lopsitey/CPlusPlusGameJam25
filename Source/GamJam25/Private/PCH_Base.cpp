// Fill out your copyright notice in the Description page of Project Settings.


#include "GamJam25/Public/PCH_Base.h"

#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"


// Sets default values
APCH_Base::APCH_Base()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArm = CreateDefaultSubobject<USpringArmComponent>("SpringArm");
	SpringArm->SetupAttachment(RootComponent);

	Camera = CreateDefaultSubobject<UCameraComponent>("Camera");
	Camera->SetupAttachment(SpringArm);

	bUseControllerRotationPitch = true;
}

// Called when the game starts or when spawned
void APCH_Base::BeginPlay()
{
	Super::BeginPlay();


	GetCharacterMovement()->MaxWalkSpeed=WalkSpeed;
}

// Called every frame
void APCH_Base::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void APCH_Base::Move_Implementation(const FInputActionInstance& Instance)
{
	IIA_Interface::Move_Implementation(Instance);
	
	if (Controller)
	{
		const FVector2D MoveValue = Instance.GetValue().Get<FVector2D>();
		const FRotator MovementRotation(0, Controller->GetControlRotation().Yaw, 0);

		if (FMath::Abs(MoveValue.Y) > KINDA_SMALL_NUMBER)
		{
			const FVector Direction = MovementRotation.RotateVector(FVector::ForwardVector);
			AddMovementInput(Direction, MoveValue.Y);
		}
		if (FMath::Abs(MoveValue.Y) > KINDA_SMALL_NUMBER)
		{
			const FVector Direction = MovementRotation.RotateVector(FVector::RightVector);
			AddMovementInput(Direction, MoveValue.X);
		}
	}
}

void APCH_Base::JumpAction_Implementation(const FInputActionInstance& Instance)
{
	IIA_Interface::JumpAction_Implementation(Instance);
	Jump();
}

void APCH_Base::Action_Implementation(const FInputActionInstance& Instance)
{
	IIA_Interface::Action_Implementation(Instance);
	bool bValue = Instance.GetValue().Get<bool>();

	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, "bValue: " + bValue);
}

void APCH_Base::Look_Implementation(const FInputActionInstance& Instance)
{
	IIA_Interface::Look_Implementation(Instance);
	if (Controller)
	{
		const FVector2D AxisValue = Instance.GetValue().Get<FVector2D>();
		if (AxisValue.X != 0)
		{
			AddControllerYawInput(AxisValue.X);
		}
		if (AxisValue.Y != 0)
		{
			AddControllerPitchInput(-AxisValue.Y);
		}
			
	}
}

// Called to bind functionality to input
void APCH_Base::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

