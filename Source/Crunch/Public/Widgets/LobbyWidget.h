// (c)2025 Ravenscroft Productions

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Player/PlayerInfoTypes.h"
#include "LobbyWidget.generated.h"

class UAbilityListView;
class ACharacterDisplay;
class ACPlayerState;
class UTileView;
class ACGameState;
class ALobbyPlayerController;
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
	UWidget* HeroSelectionRoot;
	
	UPROPERTY(meta = (BindWidget))
	UTileView* CharacterSelectionTileView;
	
	UPROPERTY(meta = (BindWidget))
	UAbilityListView* AbilityListView;
	
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
	void ConfigureGameState();
	
	FTimerHandle ConfigureGameStateTimerHandle;
	
	UPROPERTY()
	ALobbyPlayerController* LobbyPlayerController;
	
	UPROPERTY()
	ACPlayerState* CPlayerState;
	
	UPROPERTY()
	ACGameState* CGameState;
	
	void UpdatePlayerSelectionDisplay(const TArray<FPlayerSelection>& PlayerSelections);
	
	UFUNCTION()
	void StartHeroSelectionButtonClicked();
	
	void SwitchToHeroSelection();
	void CharacterDefinitionLoaded();
	void CharacterSelected(UObject* SelectedUObject);
	
	UPROPERTY(EditDefaultsOnly, Category = "Character Display")
	TSubclassOf<ACharacterDisplay> CharacterDisplayClass;
	
	UPROPERTY()
	ACharacterDisplay* CharacterDisplay;
	
	void SpawnCharacterDisplay();
	void UpdateCharacterDisplay(const FPlayerSelection& PlayerSelection);
};
