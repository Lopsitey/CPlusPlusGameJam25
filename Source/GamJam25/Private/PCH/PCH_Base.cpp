#include "PCH/PCH_Base.h"

#include "HealthComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Interactibles/InteractionInterface.h"
#include "Interactibles/Pickups/Spells/SpellBase.h"
#include "PCH/InventoryComponent.h"
#include "PCH/PCH_Anim_Interface.h"
#include "PCH/PC_Base.h"


// Sets default values
APCH_Base::APCH_Base()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArm = CreateDefaultSubobject<USpringArmComponent>("SpringArm");
	SpringArm->SetupAttachment(RootComponent);

	Camera = CreateDefaultSubobject<UCameraComponent>("Camera");
	Camera->SetupAttachment(SpringArm);

	Health=CreateDefaultSubobject<UHealthComponent>("Health");
	InventoryComp = CreateDefaultSubobject<UInventoryComponent>("Inventory");

	bUseControllerRotationYaw = true;
	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = true;
	SpringArm->bUsePawnControlRotation = true;

	Tags.Add(FName("Player"));

}

// Called when the game starts or when spawned
void APCH_Base::BeginPlay()
{
	Super::BeginPlay();

	if (Health)
	{
		Health->OnDeath.AddUniqueDynamic(this, &APCH_Base::PlayerDeath);
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, "No health component found");
	}
	
	GetCharacterMovement()->MaxWalkSpeed=WalkSpeed;

	SkeletalMesh = GetMesh();
	if (!SkeletalMesh)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, "No skeletal mesh component found");
		return;
	}
	AnimInstance = SkeletalMesh->GetAnimInstance();
	if (!AnimInstance)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, "No animation instance found");
		return;
	}

	if (InventoryComp)
	{
		InventoryComp->OnSpellChanged.AddUniqueDynamic(this, &APCH_Base::AttachSpell);
		InventoryComp->AddSpell(SpellWeapon);
	}
	
	AttachSpell();
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
		if (FMath::Abs(MoveValue.X) > KINDA_SMALL_NUMBER)
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
	if (mOverlappedActor)
	{
		
		IInteractionInterface::Execute_Interact(mOverlappedActor);	
	}
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

void APCH_Base::SetOverlappedActor_Implementation(AActor* OverlappedActor)
{
	IPCH_Interface::SetOverlappedActor_Implementation(OverlappedActor);
	mOverlappedActor = OverlappedActor;
}

void APCH_Base::SpellCast_Implementation()
{
	IPCH_Interface::SpellCast_Implementation();
	EquippedSpell->SpellCast();
}

void APCH_Base::EnableSpellCasting_Implementation(bool bEnableFire)
{
	IPCH_Interface::EnableSpellCasting_Implementation(bEnableFire);
	bCanFire=bEnableFire;
}

void APCH_Base::AddHealthFromPickup_Implementation(float val)
{
	IPCH_Interface::AddHealthFromPickup_Implementation(val);

	Health->AddHealth(val);
}

void APCH_Base::AddSpellFromPickup_Implementation(TSubclassOf<ASpellBase> Spell)
{
	IPCH_Interface::AddSpellFromPickup_Implementation(Spell);

	InventoryComp->AddSpell(Spell);
}

void APCH_Base::PlayerDeath()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, "Player Died");
	APC_Base* PC = Cast<APC_Base>(GetController());
	PC->SetIgnoreLookInput(true);
	PC->SetIgnoreMoveInput(true);
}

void APCH_Base::AttachSpell()
{
	if (!SpellWeapon)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, "No spell class or inventory assigned");
		return;
	}

	TSubclassOf<ASpellBase> SpellClass = InventoryComp->GetCurrentSpell();
	if (!SpellClass)
		return;

	if (EquippedSpell)
	{
		EquippedSpell->SetActorHiddenInGame(true);
		EquippedSpell->SetActorEnableCollision(false);
	}

	ASpellBase* CachedSpell = nullptr;

	if (SpawnedSpells.Contains(SpellClass))
	{
		CachedSpell = SpawnedSpells[SpellClass];//uses the spell class like a key to access the value in the map
	}
	else
	{
		FActorSpawnParameters SpawnParams;
		SpawnParams.Owner=this;
		SpawnParams.Instigator=GetInstigator();

		CachedSpell=GetWorld()->SpawnActor<ASpellBase>(SpellClass,FVector::ZeroVector,FRotator::ZeroRotator, SpawnParams);

		if (CachedSpell)
		{
			const FName AttachmentSocketName = FName("SpellSocket");
			CachedSpell->AttachToComponent(SkeletalMesh,FAttachmentTransformRules::SnapToTargetIncludingScale,AttachmentSocketName);
		}
	}

	if (CachedSpell)
	{
		EquippedSpell=CachedSpell;
		EquippedSpell->SetActorHiddenInGame(false);
		EquippedSpell->SetActorEnableCollision(true);
	}
	
	/*if (!EquippedSpell)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, "No spell class assigned");
		return;
	}

	const FName AttachmentSocketName = FName("SpellSocket");
	EquippedSpell->AttachToComponent(SkeletalMesh,FAttachmentTransformRules::SnapToTargetIncludingScale,AttachmentSocketName);*/
}

// Called to bind functionality to input
void APCH_Base::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void APCH_Base::Fire_Implementation(const FInputActionInstance& Instance)
{
	IIA_Interface::Fire_Implementation(Instance);
	
	if (!SkeletalMesh)
	{
		return;
	}
	if (bCanFire)
	{
		bCanFire = false;
		IPCH_Anim_Interface::Execute_PlaySpellCastAnimation(AnimInstance, true);
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, "FIRE");
	}
}

void APCH_Base::Scroll_Implementation(const FInputActionInstance& Instance)
{
	IIA_Interface::Scroll_Implementation(Instance);

	float ScrolledValue = Instance.GetValue().Get<float>();//gets the float value from the entire set of values
	UE_LOG(LogTemp, Warning, TEXT("AHHHHHHHHHHHHHHHHHHHHHHHH %f"), ScrolledValue);
	if (InventoryComp)
	{
		if (ScrolledValue>0)
			InventoryComp->NextSpell();
		if (ScrolledValue<0)
			InventoryComp->PreviousSpell();
	}
		
}


