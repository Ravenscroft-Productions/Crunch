// (c)2025 Ravenscroft Productions

#pragma once

#include "CoreMinimal.h"
#include "ItemWidget.h"
#include "InventoryItemWidget.generated.h"

class UInventoryItem;
class UTextBlock;
/**
 * 
 */
UCLASS()
class CRUNCH_API UInventoryItemWidget : public UItemWidget
{
	GENERATED_BODY()
public:
	virtual void NativeConstruct() override;
	bool IsEmpty() const;
	void UpdateInventoryItem(const UInventoryItem* Item);
	void EmptySlot();
	FORCEINLINE int GetSlotNumber() const { return SlotNumber; }
		
private:
	void UpdateStackCount();
	
	UPROPERTY(EditDefaultsOnly, Category = "Visual")
	UTexture2D* EmptyTexture;
	
	UPROPERTY(meta = (BindWidget))
	UTextBlock* StackCountText;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* CooldownCountText;

	UPROPERTY(Meta = (BindWidget))
	UTextBlock* CooldownDurationText;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* ManaCostText;

	UPROPERTY()
	const UInventoryItem* InventoryItem;

	int SlotNumber;
};
