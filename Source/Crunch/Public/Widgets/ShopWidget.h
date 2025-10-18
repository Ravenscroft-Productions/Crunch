// (c)2025 Ravenscroft Productions

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ShopWidget.generated.h"

class UItemTreeWidget;
class UInventoryComponent;
class UShopItemWidget;
class UPDA_ShopItem;
class UTileView;
/**
 * 
 */
UCLASS()
class CRUNCH_API UShopWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	virtual void NativeConstruct() override;
	
private:
	UPROPERTY(meta = (BindWidget))
	UTileView* ShopItemList;

	UPROPERTY(meta = (BindWidget))
	UItemTreeWidget* CombinationTree;

	void LoadShopItems();
	void ShopItemLoadFinished();
	void ShopItemWidgetGenerated(UUserWidget& NewWidget);

	UPROPERTY()
	TMap<const UPDA_ShopItem*, const UShopItemWidget*> ItemsMap;

	UPROPERTY()
	UInventoryComponent* OwnerInventoryComponent;

	void ShowItemCombination(const UShopItemWidget* ItemWidget);
};
