// (c)2025 Ravenscroft Productions


// ReSharper disable CppRedundantQualifier
#include "Widgets/ShopItemWidget.h"

#include "Components/ListView.h"
#include "Framework/CAssetManager.h"
#include "Inventory/PDA_ShopItem.h"

UUserWidget* UShopItemWidget::GetWidget() const
{
	UShopItemWidget* Copy = CreateWidget<UShopItemWidget>(GetOwningPlayer(), GetClass());
	Copy->CopyFromOther(this);
	return Copy;
}

TArray<const ITreeNodeInterface*> UShopItemWidget::GetInputs() const
{
	const FItemCollection* Collection = UCAssetManager::Get().GetCombinationForItem(GetShopItem());
	if (Collection) return ItemsToInterfaces(Collection->GetItems());

	return TArray<const ITreeNodeInterface*>();
}

TArray<const ITreeNodeInterface*> UShopItemWidget::GetOutputs() const
{
	const FItemCollection* Collection = UCAssetManager::Get().GetIngredientForItem(GetShopItem());
	if (Collection) return ItemsToInterfaces(Collection->GetItems());

	return TArray<const ITreeNodeInterface*>();
}

const UObject* UShopItemWidget::GetItemObject() const
{
	return ShopItem;
}

void UShopItemWidget::NativeOnListItemObjectSet(UObject* ListItemObject)
{
	IUserObjectListEntry::NativeOnListItemObjectSet(ListItemObject);
	InitWithShopItem(Cast<UPDA_ShopItem>(ListItemObject));
	ParentListView = Cast<UListView>(IUserListEntry::GetOwningListView());
}

void UShopItemWidget::CopyFromOther(const UShopItemWidget* OtherWidget)
{
	OnItemPurchaseIssued = OtherWidget->OnItemPurchaseIssued;
	OnShopItemClicked = OtherWidget->OnShopItemClicked;
	InitWithShopItem(OtherWidget->GetShopItem());
	ParentListView = OtherWidget->ParentListView;
}

void UShopItemWidget::InitWithShopItem(const UPDA_ShopItem* NewShopItem)
{
	ShopItem = NewShopItem;
	if (!ShopItem) return;
	
	SetIcon(ShopItem->GetIcon());
	SetToolTipWidget(ShopItem);
}

TArray<const ITreeNodeInterface*> UShopItemWidget::ItemsToInterfaces(const TArray<const UPDA_ShopItem*>& Items) const
{
	TArray<const ITreeNodeInterface*> RetInterfaces;
	if (!ParentListView) return RetInterfaces;

	for (const UPDA_ShopItem* Item : Items)
	{
		const UShopItemWidget* ItemWidget = ParentListView->GetEntryWidgetFromItem<UShopItemWidget>(Item);
		if (ItemWidget)
		{
			RetInterfaces.Add(ItemWidget);
		}
	}

	return RetInterfaces;
}

void UShopItemWidget::RightButtonClicked()
{
	OnItemPurchaseIssued.Broadcast(GetShopItem());
}

void UShopItemWidget::LeftButtonClicked()
{
	OnShopItemClicked.Broadcast(this);
}
