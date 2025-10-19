// (c)2025 Ravenscroft Productions

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ItemWidget.generated.h"

class UPDA_ShopItem;
class UItemToolTip;
class UImage;
/**
 * 
 */
UCLASS()
class CRUNCH_API UItemWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	virtual void NativeConstruct() override;
	virtual void SetIcon(UTexture2D* IconTexture);

protected:
	UItemToolTip* SetToolTipWidget(const UPDA_ShopItem* Item);
	UImage* GetItemIcon() const { return ItemIcon; }

private:
	UPROPERTY(meta=(BindWidget))
	UImage* ItemIcon;

	UPROPERTY(EditDefaultsOnly, Category = "ToolTip")
	TSubclassOf<UItemToolTip> ItemToolTipClass;

	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	virtual FReply NativeOnMouseButtonUp(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;

	virtual void RightButtonClicked();
	virtual void LeftButtonClicked();
};
