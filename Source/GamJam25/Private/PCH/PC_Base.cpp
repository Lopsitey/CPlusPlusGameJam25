#include "GamJam25/Public/PCH/PC_Base.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "HealthComponent.h"
#include "My_GM.h"
#include "Blueprint/UserWidget.h"
#include "GamJam25/Public/PCH/Inputs/IADataConfig.h"
#include "GamJam25/Public/PCH/Inputs/IA_Interface.h"
#include "PCH/HealthInterface.h"
#include "PCH/HUD/PlayerHUD.h"

void APC_Base::BeginPlay()
{
	Super::BeginPlay();
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(
		GetLocalPlayer()))
	{
		if (MappingContext)
		{
			Subsystem->ClearAllMappings();
			Subsystem->AddMappingContext(MappingContext, 0);
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
		PEI->BindAction(InputActions->Move.LoadSynchronous(), ETriggerEvent::Triggered, this, &APC_Base::Move);
		PEI->BindAction(InputActions->Look.LoadSynchronous(), ETriggerEvent::Triggered, this, &APC_Base::Look);
		PEI->BindAction(InputActions->Jump.LoadSynchronous(), ETriggerEvent::Triggered, this, &APC_Base::Jump);
		PEI->BindAction(InputActions->Action.LoadSynchronous(), ETriggerEvent::Triggered, this, &APC_Base::Action);
		PEI->BindAction(InputActions->Fire.LoadSynchronous(), ETriggerEvent::Triggered, this, &APC_Base::Fire);
		PEI->BindAction(InputActions->Scroll.LoadSynchronous(), ETriggerEvent::Triggered, this, &APC_Base::Scroll);
	}
}

void APC_Base::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	LocalPCH = GetPawn();

	if (auto* HealthCompInterface = Cast<
		IHealthInterface>(InPawn->GetComponentByClass(UHealthInterface::StaticClass())))
	{
		auto& HealthDelegate = HealthCompInterface->GetHealthChangedDelegate();
		HealthDelegate.AddDynamic(this, &APC_Base::UpdateHealth);
		//add dynamic allows multiple bindings whereas add dynamic unique only allows one

		if (IsLocalController() && HUDClass)
		{
			ActiveHUD = CreateWidget<UPlayerHUD>(this, HUDClass);
			if (ActiveHUD)
			{
				ActiveHUD->AddToViewport();
				ActiveHUD->SetMaxHealth(HealthCompInterface->GetMaxHealth());
				ActiveHUD->OnScoreChanged(0); //initial score display todo  - may want to store score somewhere
			}
		}
	}
}

void APC_Base::OnUnPossess()
{
	if (auto* HealthCompInterface = Cast<IHealthInterface>(
		LocalPCH->GetComponentByClass(UHealthComponent::StaticClass())))
	{
		HealthCompInterface->GetHealthChangedDelegate().RemoveDynamic(this, &APC_Base::UpdateHealth);
	}

	Super::OnUnPossess();
}

void APC_Base::Move(const FInputActionInstance& Instance)
{
	IIA_Interface::Execute_Move(LocalPCH, Instance);
}

void APC_Base::Look(const FInputActionInstance& Instance)
{
	IIA_Interface::Execute_Look(LocalPCH, Instance);
}

void APC_Base::Jump(const FInputActionInstance& Instance)
{
	IIA_Interface::Execute_JumpAction(LocalPCH, Instance);
}

void APC_Base::Action(const FInputActionInstance& Instance)
{
	IIA_Interface::Execute_Action(LocalPCH, Instance);
}

void APC_Base::Fire(const FInputActionInstance& Instance)
{
	IIA_Interface::Execute_Fire(LocalPCH, Instance);
}

void APC_Base::Scroll(const FInputActionInstance& Instance)
{
	IIA_Interface::Execute_Scroll(LocalPCH, Instance);
}

void APC_Base::UpdateScore(uint8 score)
{
	GEngine->AddOnScreenDebugMessage(-1, 20.f, FColor::Blue, FString::Printf(TEXT("Score: %d"), score));
	//for printing types which aren't string

	ActiveHUD->OnScoreChanged(score);
}

void APC_Base::GameWin()
{
	GEngine->AddOnScreenDebugMessage(-1, 20.f, FColor::Green, TEXT("You Win!"));
}

void APC_Base::UpdateHealth(float NewHealth)
{
	ActiveHUD->OnHealthChanged(NewHealth);
}
