// (c)2025 Ravenscroft Productions


#include "Player/LobbyPlayerController.h"
#include "Player/CPlayerState.h"
#include "Framework/CGameState.h"

void ALobbyPlayerController::Server_RequestSlotSelectionChange_Implementation(uint8 NewSlotID)
{
	if (!GetWorld()) return;
	
	ACGameState* CGameState = GetWorld()->GetGameState<ACGameState>();
	if (!CGameState) return;
	
	CGameState->RequestPlayerSelectionChange(GetPlayerState<APlayerState>(), NewSlotID);		
}

bool ALobbyPlayerController::Server_RequestSlotSelectionChange_Validate(uint8 NewSlotID)
{
	return true;
}
