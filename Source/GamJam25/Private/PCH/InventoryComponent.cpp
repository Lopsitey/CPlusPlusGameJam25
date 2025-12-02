#include "PCH/InventoryComponent.h"

#include "SNegativeActionButton.h"
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
	/*
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
	*/
	if (!NewSpell)
		return;

	//If the spell already exists
	if (AvailableSpells.Contains(NewSpell))
	{
		//Keep order in SpellKeys: ensure it contains the key
		if (!SpellKeys.Contains(NewSpell))
		{
			SpellKeys.Add(NewSpell);
		}

		OnSpellChanged.Broadcast();
		return;
	}

	//add the new spell to both the map and the ordered list
	AvailableSpells.Add(NewSpell, 0); // default ammo 0
	SpellKeys.Add(NewSpell);

	//If this is the first spell, select it
	if (SpellKeys.Num() == 1)
	{
		CurrentSpellIndex = 0;
	}
	
	OnSpellChanged.Broadcast();
}

void UInventoryComponent::RemoveSpell(TSubclassOf<ASpellBase> ToRemove)
{
	if (!ToRemove)
		return;

	if (!AvailableSpells.Contains(ToRemove) && !SpellKeys.Contains(ToRemove))
		return;

	AvailableSpells.Remove(ToRemove);
	SpellKeys.Remove(ToRemove);
	
	if (SpellKeys.Num()==0)//resets for empty spells
	{
		CurrentSpellIndex=0;
		OnSpellChanged.Broadcast();
		return;
	}
	
	// Clamp the Index so it always references a valid entry
	
	if (CurrentSpellIndex >= SpellKeys.Num())
	{
		CurrentSpellIndex = SpellKeys.Num() - 1;
	}
	
	OnSpellChanged.Broadcast();
	UE_LOG(LogTemp, Warning, TEXT("Spell Removed!"));
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


void UInventoryComponent::TryScroll(int32 Direction)
{
	if (SpellKeys.Num() == 0)
		return;
	
	const int32 OldIndex = CurrentSpellIndex;
	//% caps it at less than the amount of spells you have
	int32 NewIndex = (CurrentSpellIndex + Direction + SpellKeys.Num()) % SpellKeys.Num();

	TSubclassOf<ASpellBase> SpellClass = SpellKeys[NewIndex];

	uint8 storedAmmo = GetStoredAmmo(SpellClass);

	// If spell has no ammo → remove it and DO NOT scroll to it.
	if (storedAmmo == 0)
	{
		RemoveSpell(SpellClass);

		//prevents trying to divide by 0 if you removed all of your spells or haven't added any yet
		if (SpellKeys.Num() == 0)
			return;

		// Keep scrolling in the same direction
		NewIndex = (OldIndex + Direction + SpellKeys.Num()) % SpellKeys.Num();
	}

	CurrentSpellIndex = NewIndex;
	OnSpellChanged.Broadcast();
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
