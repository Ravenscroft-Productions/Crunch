// (c)2025 Ravenscroft Productions

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "Player/PlayerInfoTypes.h"
#include "CGameState.generated.h"

class UPA_CharacterDefinition;
DECLARE_MULTICAST_DELEGATE_OneParam(FOnPlayerSelectionUpdated, const TArray<FPlayerSelection>& /*NewPlayerSelection*/);
/**
 * 
 */
UCLASS()
class CRUNCH_API ACGameState : public AGameStateBase
{
	GENERATED_BODY()
public:
	FOnPlayerSelectionUpdated OnPlayerSelectionUpdated;
	
	void RequestPlayerSelectionChange(const APlayerState* RequestingPlayer, uint8 DesiredSlot);
	void SetCharacterSelected(const APlayerState* SelectingPlayer, const UPA_CharacterDefinition* SelectedDefinition);
	bool IsSlotOccupied(uint8 SlotId) const;
	bool IsDefinitionSelected(const UPA_CharacterDefinition* Definition) const;
	void SetCharacterDeselected(const UPA_CharacterDefinition* DefinitionToDeselect);
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	const TArray<FPlayerSelection>& GetPlayerSelection() const;
	bool CanStartHeroSelection() const;
	bool CanStartMatch() const;
	
private:
	UPROPERTY(ReplicatedUsing = OnRep_PlayerSelectionArray)
	TArray<FPlayerSelection> PlayerSelectionArray;
	
	UFUNCTION()
	void OnRep_PlayerSelectionArray();
};
