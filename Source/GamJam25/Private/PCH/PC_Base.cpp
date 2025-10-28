// Fill out your copyright notice in the Description page of Project Settings.


#include "GamJam25/Public/PCH/PC_Base.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "My_GM.h"
#include "GamJam25/PCH/Inputs/IADataConfig.h"
#include "GamJam25/Public/PCH/Inputs/IA_Interface.h"

void APC_Base::BeginPlay()
{
	Super::BeginPlay();
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		if (MappingContext)
		{
			Subsystem->ClearAllMappings();
			Subsystem->AddMappingContext(MappingContext,0);
		}
	}
	if (GetPawn())
	{
		LocalPCH = GetPawn();	
	}

	if (AMy_GM* GM = Cast<AMy_GM>(GetWorld()->GetAuthGameMode()))
	{
		GM->OnUpdateCollectibles.AddUniqueDynamic(this, &APC_Base::UpdateScore);
		GM->CollectiblesComplete.AddUniqueDynamic(this, &APC_Base::GameWin);
	}
}

void APC_Base::SetupInputComponent()
{
	Super::SetupInputComponent();
	
	if (UEnhancedInputComponent* PEI = Cast<UEnhancedInputComponent>(InputComponent))
	{
		PEI->BindAction(InputActions->Move.LoadSynchronous(),ETriggerEvent::Triggered, this, &APC_Base::Move);
		PEI->BindAction(InputActions->Look.LoadSynchronous(),ETriggerEvent::Triggered, this, &APC_Base::Look);
		PEI->BindAction(InputActions->Jump.LoadSynchronous(),ETriggerEvent::Triggered, this, &APC_Base::Jump);
		PEI->BindAction(InputActions->Action.LoadSynchronous(),ETriggerEvent::Triggered, this, &APC_Base::Action);
		PEI->BindAction(InputActions->Fire.LoadSynchronous(),ETriggerEvent::Triggered, this, &APC_Base::Fire);
	}
}

void APC_Base::Move(const FInputActionInstance& Instance)
{
	IIA_Interface::Execute_Move(LocalPCH,Instance);
}

void APC_Base::Look(const FInputActionInstance& Instance)
{
	IIA_Interface::Execute_Look(LocalPCH,Instance);
}

void APC_Base::Jump(const FInputActionInstance& Instance)
{
	IIA_Interface::Execute_JumpAction(LocalPCH,Instance);
}

void APC_Base::Action(const FInputActionInstance& Instance)
{
	IIA_Interface::Execute_Action(LocalPCH,Instance);
}

void APC_Base::Fire(const FInputActionInstance& Instance)
{
	IIA_Interface::Execute_Fire(LocalPCH,Instance);
}

void APC_Base::UpdateScore(uint8 score)
{
	GEngine->AddOnScreenDebugMessage(-1,20.f,FColor::Blue, FString::Printf(TEXT("Score: %d"), score));
	//for printing types which aren't string 
}

void APC_Base::GameWin()
{
	GEngine->AddOnScreenDebugMessage(-1,20.f,FColor::Green, TEXT("You Win!"));
}
