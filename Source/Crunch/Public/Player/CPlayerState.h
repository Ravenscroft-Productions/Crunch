// (c)2025 Ravenscroft Productions

#pragma once

#include "CoreMinimal.h"
#include "PlayerInfoTypes.h"
#include "GameFramework/PlayerState.h"
#include "CPlayerState.generated.h"

class ACGameState;
/**
 * 
 */
UCLASS()
class CRUNCH_API ACPlayerState : public APlayerState
{
	GENERATED_BODY()
public:
	ACPlayerState();
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	virtual void BeginPlay() override;
	
	UFUNCTION(Server, Reliable, WithValidation)
	void Server_SetSelectedCharacterDefinition(const UPA_CharacterDefinition* NewDefinition);
	
private:
	UPROPERTY(Replicated)
	FPlayerSelection PlayerSelection;
	
	UPROPERTY()
	ACGameState* CGameState;
	
	void PlayerSelectionUpdated(const TArray<FPlayerSelection>& NewPlayerSelections);
};
