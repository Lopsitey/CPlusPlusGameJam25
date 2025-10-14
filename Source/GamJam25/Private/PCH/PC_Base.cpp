// Fill out your copyright notice in the Description page of Project Settings.


#include "GamJam25/Public/PCH/PC_Base.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
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
}

void APC_Base::SetupInputComponent()
{
	if (UEnhancedInputComponent* PEI = Cast<UEnhancedInputComponent>(InputComponent))
	{
		PEI->BindAction(InputActions->Move.LoadSynchronous(),ETriggerEvent::Triggered, this, &APC_Base::Move);
		PEI->BindAction(InputActions->Look.LoadSynchronous(),ETriggerEvent::Triggered, this, &APC_Base::Look);
		PEI->BindAction(InputActions->Jump.LoadSynchronous(),ETriggerEvent::Triggered, this, &APC_Base::Jump);
		PEI->BindAction(InputActions->Action.LoadSynchronous(),ETriggerEvent::Triggered, this, &APC_Base::Action);
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
