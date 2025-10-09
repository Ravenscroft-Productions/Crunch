// (c)2025 Ravenscroft Productions

#pragma once

#include "CoreMinimal.h"
#include "ItemWidget.h"
#include "Blueprint/IUserObjectListEntry.h"
#include "ShopItemWidget.generated.h"

class UShopItemWidget;
class UPDA_ShopItem;

DECLARE_MULTICAST_DELEGATE_OneParam(FOnItemPurchaseIssued, const UPDA_ShopItem*);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnShopItemSelected, const UShopItemWidget*);
/**
 * 
 */
UCLASS()
class CRUNCH_API UShopItemWidget : public UItemWidget, public IUserObjectListEntry
{
	GENERATED_BODY()
public:
	FOnItemPurchaseIssued OnItemPurchaseIssued;
	FOnShopItemSelected OnShopItemClicked;
	
	virtual void NativeOnListItemObjectSet(UObject* ListItemObject) override;
	FORCEINLINE const UPDA_ShopItem* GetShopItem() const { return ShopItem; }

private:
	UPROPERTY()
	const UPDA_ShopItem* ShopItem;
	virtual void RightButtonClicked() override;
	virtual void LeftButtonClicked() override;
};
