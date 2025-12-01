#include "Interactibles/Pickups/Spells/SpellBase.h"

#include "Enemies/Projectile_Base.h"


// Sets default values
ASpellBase::ASpellBase()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

void ASpellBase::SpellCast_Implementation()
{
}

void ASpellBase::AltSpellCast_Implementation()
{
}

void ASpellBase::Charge_Implementation()
{
	uint8 ToReload = FMath::Clamp(CurrentReserve - (MaxAmmo - CurrentAmmo), 0, MaxAmmo);

	CurrentAmmo += ToReload;
	CurrentReserve -= ToReload;
}

void ASpellBase::SetAmmo_Implementation(uint8 ammo)
{
	CurrentAmmo = FMath::Clamp(ammo, 0, MaxAmmo);
	CurrentReserve = ammo > MaxAmmo ? ammo - MaxAmmo : 0;
}

uint8 ASpellBase::GetTotalAmmo_Implementation()
{
	return CurrentAmmo+CurrentReserve;
}

// Called when the game starts or when spawned
void ASpellBase::BeginPlay()
{
	Super::BeginPlay();

	CurrentAmmo = MaxAmmo;
	CurrentReserve = MaxReserve;
}

void ASpellBase::SpawnProjectile_Implementation()
{
	FTransform SpawnTransform = GetProjectileTransform();

	AProjectile_Base* Projectile = GetWorld()->SpawnActor<AProjectile_Base>(
		ProjectileClass, SpawnTransform.GetLocation(), SpawnTransform.GetRotation().Rotator());
	Projectile->SetIgnoredActors(this, GetOwner());
}

void ASpellBase::ModifyAmmo_Implementation(uint8 ReductionAmt)
{
	CurrentAmmo = FMath::Clamp(CurrentAmmo - ReductionAmt, 0, MaxAmmo);

	// Notifies the owner's inventory so the map stays in sync
	InvComp->StoreAmmo(GetClass(), GetTotalAmmo()); // update map
	//Auto-removes spell if no ammo left
	if (InvComp->GetStoredAmmo(GetClass()) == 0)
	{
		InvComp->RemoveSpell(GetClass());
	}
}

void ASpellBase::HandleEmpty_Implementation()
{
	if (bAllowedAutoReload)
		Charge();
	else
	{
		//todo vfx?
	}
}

FTransform ASpellBase::GetProjectileTransform()
{
	return FTransform(GetActorRotation(), GetActorLocation());
}

// Called every frame
void ASpellBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
