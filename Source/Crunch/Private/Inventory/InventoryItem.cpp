// (c)2025 Ravenscroft Productions


#include "Inventory/InventoryItem.h"

#include "AbilitySystemComponent.h"
#include "Inventory/PDA_ShopItem.h"

FInventoryItemHandle::FInventoryItemHandle()
	: HandleId(GetInvalidId())
{	
}

FInventoryItemHandle FInventoryItemHandle::InvalidHandle()
{
	static FInventoryItemHandle InvalidHandle = FInventoryItemHandle();
	return InvalidHandle;
}

FInventoryItemHandle::FInventoryItemHandle(uint32 Id)
	: HandleId(Id)
{	
}

FInventoryItemHandle FInventoryItemHandle::CreateHandle()
{
	return FInventoryItemHandle(GenerateNextId());
}

bool FInventoryItemHandle::IsValid() const
{
	return HandleId != GetInvalidId();
}

uint32 FInventoryItemHandle::GenerateNextId()
{
	static uint32 StaticId = 1;
	return StaticId++;
}

uint32 FInventoryItemHandle::GetInvalidId()
{
	return 0;
}

bool operator==(const FInventoryItemHandle& Lhs, const FInventoryItemHandle& Rhs)
{
	return Lhs.GetHandleId() == Rhs.GetHandleId();
}

uint32 GetTypeHash(const FInventoryItemHandle& Key)
{
	return Key.GetHandleId();
}

bool UInventoryItem::AddStackCount()
{
	if (IsStackFull()) return false;

	++StackCount;
	return true;
}

bool UInventoryItem::ReduceStackCount()
{
	--StackCount;
	if (StackCount <= 0)
	{
		return false;
	}

	return true;
}

bool UInventoryItem::SetStackCount(int NewStackCount)
{
	if (NewStackCount > 0 && NewStackCount <= GetShopItem()->GetMaxStackCount())
	{
		StackCount = NewStackCount;
		return true;
	}
	
	return false;
}

bool UInventoryItem::IsStackFull() const
{
	return StackCount >= GetShopItem()->GetMaxStackCount();
}

bool UInventoryItem::IsForItem(const UPDA_ShopItem* Item) const
{
	if (!Item) return false;

	return GetShopItem() == Item;
}

UInventoryItem::UInventoryItem()
	: StackCount(1)
{	
}

bool UInventoryItem::IsValid() const
{
	return ShopItem != nullptr;
}

void UInventoryItem::InitItem(const FInventoryItemHandle& NewHandle, const UPDA_ShopItem* NewShopItem)
{
	Handle = NewHandle;
	ShopItem = NewShopItem;
}

bool UInventoryItem::TryActivateGrantedAbility(UAbilitySystemComponent* AbilitySystemComponent)
{
	if (!GrantedAbilitySpecHandle.IsValid()) return false;

	if (AbilitySystemComponent && AbilitySystemComponent->TryActivateAbility(GrantedAbilitySpecHandle)) return true;

	return false;
}

void UInventoryItem::ApplyConsumeEffect(UAbilitySystemComponent* AbilitySystemComponent)
{
	if (!ShopItem) return;

	TSubclassOf<UGameplayEffect> ConsumeEffect = ShopItem->GetConsumeEffect();
	if (!ConsumeEffect) return;
	
	AbilitySystemComponent->BP_ApplyGameplayEffectToSelf(ConsumeEffect, 1, AbilitySystemComponent->MakeEffectContext());	
}

void UInventoryItem::RemoveGASModifications(UAbilitySystemComponent* AbilitySystemComponent)
{
	if (!AbilitySystemComponent) return;

	if (AppliedEquippedEffectHandle.IsValid())
	{
		AbilitySystemComponent->RemoveActiveGameplayEffect(AppliedEquippedEffectHandle);
	}

	if (GrantedAbilitySpecHandle.IsValid())
	{
		AbilitySystemComponent->SetRemoveAbilityOnEnd(GrantedAbilitySpecHandle);
	}
}

void UInventoryItem::ApplyGASModifications(UAbilitySystemComponent* AbilitySystemComponent)
{
	if (!GetShopItem() || !AbilitySystemComponent) return;

	if (!AbilitySystemComponent->GetOwner() || !AbilitySystemComponent->GetOwner()->HasAuthority()) return;

	TSubclassOf<UGameplayEffect> EquipEffect = GetShopItem()->GetEquippedEffect();
	if (EquipEffect)
	{
		AppliedEquippedEffectHandle = AbilitySystemComponent->BP_ApplyGameplayEffectToSelf(EquipEffect, 1, AbilitySystemComponent->MakeEffectContext());
	}

	TSubclassOf<UGameplayAbility> GrantedAbility = GetShopItem()->GetGrantedAbility();
	if (GrantedAbility)
	{
		const FGameplayAbilitySpec* FoundSpec = AbilitySystemComponent->FindAbilitySpecFromClass(GrantedAbility);
		if (FoundSpec)
		{
			GrantedAbilitySpecHandle = FoundSpec->Handle;
		}
		else
		{
			GrantedAbilitySpecHandle = AbilitySystemComponent->GiveAbility(FGameplayAbilitySpec(GrantedAbility));
		}
		
	}
}

void UInventoryItem::SetSlot(int NewSlot)
{
	Slot = NewSlot;
}
