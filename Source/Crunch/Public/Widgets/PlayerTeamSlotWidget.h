// (c)2025 Ravenscroft Productions

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PlayerTeamSlotWidget.generated.h"

class UPA_CharacterDefinition;
class UTextBlock;
class UImage;
/**
 * 
 */
UCLASS()
class CRUNCH_API UPlayerTeamSlotWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	virtual void NativeConstruct() override;
	void UpdateSlot(const FString& PlayerName, const UPA_CharacterDefinition* CharacterDefinition);
	
	virtual void NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	virtual void NativeOnMouseLeave(const FPointerEvent& InMouseEvent) override;
	
private:
	UPROPERTY(Transient, meta=(BindWidgetAnim))
	UWidgetAnimation* HoverAnim;
	
	UPROPERTY(meta = (BindWidget))
	UImage* PlayerCharacterIcon;
	
	UPROPERTY(meta = (BindWidget))
	UTextBlock* NameText;
	
	UPROPERTY(EditDefaultsOnly, Category = "Visual")
	FName CharacterIconMatParamName = "Icon";
	
	UPROPERTY(EditDefaultsOnly, Category = "Visual")
	FName CharacterEmptyMatParamName = "Empty";
	
	FString CachedPlayerNameStr;
	FString CachedCharacterNameStr;
	
	void UpdateNameText();
};
