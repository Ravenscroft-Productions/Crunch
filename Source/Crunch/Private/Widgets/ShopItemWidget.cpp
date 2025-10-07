// (c)2025 Ravenscroft Productions


#include "Widgets/ShopItemWidget.h"

#include "Inventory/PDA_ShopItem.h"

void UShopItemWidget::NativeOnListItemObjectSet(UObject* ListItemObject)
{
	IUserObjectListEntry::NativeOnListItemObjectSet(ListItemObject);

	ShopItem = Cast<UPDA_ShopItem>(ListItemObject);
	if (!ShopItem) return;
	
	SetIcon(ShopItem->GetIcon());
}
