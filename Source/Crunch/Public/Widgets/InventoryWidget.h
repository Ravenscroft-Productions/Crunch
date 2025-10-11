// (c)2025 Ravenscroft Productions

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Inventory/InventoryItem.h"
#include "InventoryWidget.generated.h"

class UInventoryComponent;
class UInventoryItemWidget;
class UWrapBox;
/**
 * 
 */
UCLASS()
class CRUNCH_API UInventoryWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	virtual void NativeConstruct() override;
	
private:
	UPROPERTY(meta = (BindWidget))
	UWrapBox* ItemList;

	UPROPERTY(EditDefaultsOnly, Category = "Inventory")
	TSubclassOf<UInventoryItemWidget> ItemWidgetClass;

	UPROPERTY()
	UInventoryComponent* InventoryComponent;

	TArray<UInventoryItemWidget*> ItemWidgets;
	TMap<FInventoryItemHandle, UInventoryItemWidget*> PopulatedItemEntryWidgets;

	void ItemAdded(const UInventoryItem* InventoryItem);
	void ItemStackCountChanged(const FInventoryItemHandle& Handle, int NewCount);

	UInventoryItemWidget* GetNextAvailableSlot() const;
};
