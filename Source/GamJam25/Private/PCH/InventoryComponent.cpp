#include "PCH/InventoryComponent.h"
#include "GamJam25/Public/Interactibles/Pickups/Spells/SpellBase.h"

// Sets default values for this component's properties
UInventoryComponent::UInventoryComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UInventoryComponent::AddSpell(TSubclassOf<ASpellBase> NewSpell)
{
	if (!SpellKeys.Contains(NewSpell))
	{
		SpellKeys.Add(NewSpell);

		if (!AvailableSpells.Contains(NewSpell))
		{
			AvailableSpells.Add(NewSpell);
		}
		
		if (SpellKeys.Num() == 1)
		{
			CurrentSpellIndex = 0;
			OnSpellChanged.Broadcast();
		}
	}
}

void UInventoryComponent::RemoveSpell(TSubclassOf<ASpellBase> ToRemove)
{
	if (!AvailableSpells.Contains(ToRemove))
		return;

	AvailableSpells.Remove(ToRemove);
	SpellKeys.Remove(ToRemove);

	if (SpellKeys.Num() == 0) //prevents trying to divide by 0 if you remove your final spell
		return;
	CurrentSpellIndex = ((CurrentSpellIndex - 1) + SpellKeys.Num()) % SpellKeys.Num();
}

void UInventoryComponent::NextSpell()
{
	if (SpellKeys.Num() == 0)
		return;
	CurrentSpellIndex = (CurrentSpellIndex + 1) % SpellKeys.Num(); //caps it at less than the amount of spells you have
	OnSpellChanged.Broadcast();
}

void UInventoryComponent::PreviousSpell()
{
	if (SpellKeys.Num() == 0)
		return;

	CurrentSpellIndex = ((CurrentSpellIndex - 1) + SpellKeys.Num()) % SpellKeys.Num();
	OnSpellChanged.Broadcast();
}

TSubclassOf<ASpellBase> UInventoryComponent::GetCurrentSpell()
{
	if (SpellKeys.IsValidIndex(CurrentSpellIndex))
		return SpellKeys[CurrentSpellIndex];

	return nullptr;
}

uint8 UInventoryComponent::GetStoredAmmo(TSubclassOf<ASpellBase> spell)
{
	return AvailableSpells.Contains(spell) ? AvailableSpells[spell] : 0;
}

void UInventoryComponent::StoreAmmo(TSubclassOf<ASpellBase> spell, uint8 ammo)
{
	AvailableSpells.FindOrAdd(spell) = ammo;
}


// Called when the game starts
void UInventoryComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
}


// Called every frame
void UInventoryComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                        FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}
