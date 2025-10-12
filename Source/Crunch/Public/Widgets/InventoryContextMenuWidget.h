// (c)2025 Ravenscroft Productions

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "InventoryContextMenuWidget.generated.h"

/**
 * 
 */
UCLASS()
class CRUNCH_API UInventoryContextMenuWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	FOnButtonClickedEvent& GetSellButtonClickedEvent() const;
	FOnButtonClickedEvent& GetUseButtonClickedEvent() const;

private:
	UPROPERTY(meta = (BindWidget))
	UButton* SellButton;

	UPROPERTY(meta = (BindWidget))
	UButton* UseButton;
};
