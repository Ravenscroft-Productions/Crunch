// (c)2025 Ravenscroft Productions


#include "Inventory/PDA_ShopItem.h"

#include "Abilities/GameplayAbility.h"

FItemCollection::FItemCollection()
	:Items()
{
}

FItemCollection::FItemCollection(const TArray<const UPDA_ShopItem*>& InItems)
	:Items(InItems)
{
}

void FItemCollection::AddItem(const UPDA_ShopItem* NewItem, bool bAddUnique)
{
	if (bAddUnique && Items.Contains(NewItem)) return;

	Items.Add(NewItem);
}

bool FItemCollection::Contains(const UPDA_ShopItem* Item) const
{
	return Items.Contains(Item);
}

const TArray<const UPDA_ShopItem*>& FItemCollection::GetItems() const
{
	return Items;
}

FPrimaryAssetId UPDA_ShopItem::GetPrimaryAssetId() const
{
	return FPrimaryAssetId(GetShopItemAssetType(), GetFName());
}

FPrimaryAssetType UPDA_ShopItem::GetShopItemAssetType()
{
	return FPrimaryAssetType("ShopItem");
}

UTexture2D* UPDA_ShopItem::GetIcon() const
{
	return Icon.LoadSynchronous();
}

UGameplayAbility* UPDA_ShopItem::GetGrantedAbilityCDO() const
{
	if (GrantedAbility)
	{
		return Cast<UGameplayAbility>(GrantedAbility->GetDefaultObject());
	}
	
	return nullptr;
}
