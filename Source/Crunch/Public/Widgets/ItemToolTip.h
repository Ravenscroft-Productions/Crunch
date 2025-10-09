// (c)2025 Ravenscroft Productions

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ItemToolTip.generated.h"

class UPDA_ShopItem;
class UTextBlock;
class UImage;
/**
 * 
 */
UCLASS()
class CRUNCH_API UItemToolTip : public UUserWidget
{
	GENERATED_BODY()
public:
	void SetItem(const UPDA_ShopItem* Item);
	void SetPrice(float newPrice);
	
private:
	UPROPERTY(meta=(BindWidget))
	UImage* IconImage;

	UPROPERTY(meta=(BindWidget))
	UTextBlock* ItemTitleText;

	UPROPERTY(meta=(BindWidget))
	UTextBlock* ItemDescriptionText;

	UPROPERTY(meta=(BindWidget))
	UTextBlock* ItemPriceText;
};
