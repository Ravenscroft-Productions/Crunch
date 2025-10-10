// (c)2025 Ravenscroft Productions


#include "Inventory/InventoryComponent.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "GAS/CHeroAttributeSet.h"
#include "Inventory/InventoryItem.h"
#include "Inventory/PDA_ShopItem.h"


UInventoryComponent::UInventoryComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UInventoryComponent::TryPurchase(const UPDA_ShopItem* ItemToPurchase)
{
	if (!OwnerAbilitySystemComponent) return;

	Server_Purchase(ItemToPurchase);
}

float UInventoryComponent::GetGold() const
{
	bool bFound = false;
	if (OwnerAbilitySystemComponent)
	{
		float Gold = OwnerAbilitySystemComponent->GetGameplayAttributeValue(UCHeroAttributeSet::GetGoldAttribute(), bFound);
		if (bFound)
		{
			return Gold;
		}
	}

	return 0.0f;
}

void UInventoryComponent::BeginPlay()
{
	Super::BeginPlay();

	OwnerAbilitySystemComponent = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(GetOwner());	
}

void UInventoryComponent::GrantItem(const UPDA_ShopItem* NewItem)
{
	if (!GetOwner()->HasAuthority()) return;

	UInventoryItem* InventoryItem = NewObject<UInventoryItem>();
	FInventoryItemHandle NewHandle = FInventoryItemHandle::CreateHandle();
	InventoryItem->InitItem(NewHandle, NewItem);
	InventoryMap.Add(NewHandle, InventoryItem);
	OnItemAdded.Broadcast(InventoryItem);
	UE_LOG(LogTemp, Warning, TEXT("Server Adding Shop Item: %s, with Id: %d"), *InventoryItem->GetShopItem()->GetItemName().ToString(), NewHandle.GetHandleId());
	Client_ItemAdded(NewHandle, NewItem);
	InventoryItem->ApplyGASModifications(OwnerAbilitySystemComponent);
}

void UInventoryComponent::Client_ItemAdded_Implementation(FInventoryItemHandle AssignedHandle, const UPDA_ShopItem* Item)
{
	if (GetOwner()->HasAuthority()) return;

	UInventoryItem* InventoryItem = NewObject<UInventoryItem>();
	InventoryItem->InitItem(AssignedHandle, Item);
	InventoryMap.Add(AssignedHandle, InventoryItem);
	OnItemAdded.Broadcast(InventoryItem);
	UE_LOG(LogTemp, Warning, TEXT("Client Adding Shop Item: %s, with Id: %d"), *InventoryItem->GetShopItem()->GetItemName().ToString(), AssignedHandle.GetHandleId());
}

void UInventoryComponent::Server_Purchase_Implementation(const UPDA_ShopItem* ItemToPurchase)
{
	if (!ItemToPurchase) return;

	if (GetGold() < ItemToPurchase->GetPrice()) return;

	OwnerAbilitySystemComponent->ApplyModToAttribute(UCHeroAttributeSet::GetGoldAttribute(), EGameplayModOp::Additive, -ItemToPurchase->GetPrice());
	GrantItem(ItemToPurchase);
}

bool UInventoryComponent::Server_Purchase_Validate(const UPDA_ShopItem* ItemToPurchase)
{
	return true;
}
