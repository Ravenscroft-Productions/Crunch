// (c)2025 Ravenscroft Productions

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "LobbyWidget.generated.h"

class UTeamSelectionWidget;
class UUniformGridPanel;
class UButton;
class UWidgetSwitcher;
/**
 * 
 */
UCLASS()
class CRUNCH_API ULobbyWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	virtual void NativeConstruct() override;
	
private:
	UPROPERTY(meta = (BindWidget))
	UWidgetSwitcher* MainSwitcher;
	
	UPROPERTY(meta = (BindWidget))
	UWidget* TeamSelectionRoot;
	
	UPROPERTY(meta = (BindWidget))
	UButton* StartHeroSelectionButton;
	
	UPROPERTY(meta = (BindWidget))
	UUniformGridPanel* TeamSelectionSlotGridPanel;
	
	UPROPERTY(EditDefaultsOnly, Category = "TeamSelection")
	TSubclassOf<UTeamSelectionWidget> TeamSelectionWidgetClass;
	
	UPROPERTY()
	TArray<UTeamSelectionWidget*> TeamSelectionSlots;
	
	void ClearAndPopulateTeamSelectionSlots();
	void SlotSelected(uint8 NewSlotID);
};
