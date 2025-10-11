// (c)2025 Ravenscroft Productions

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/DragDropOperation.h"
#include "InventoryItemDragDropOp.generated.h"

class UItemWidget;
class UInventoryItemWidget;
/**
 * 
 */
UCLASS()
class CRUNCH_API UInventoryItemDragDropOp : public UDragDropOperation
{
	GENERATED_BODY()
public:
	void SetDraggedItem(UInventoryItemWidget* DraggedItem);

private:
	UPROPERTY(EditDefaultsOnly, Category = "Visual")
	TSubclassOf<UItemWidget> DragVisualClass;
};
