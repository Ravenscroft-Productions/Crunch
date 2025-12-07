// (c)2025 Ravenscroft Productions

#pragma once

#include "CoreMinimal.h"
#include "MenuPlayerController.h"
#include "LobbyPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class CRUNCH_API ALobbyPlayerController : public AMenuPlayerController
{
	GENERATED_BODY()
public:
	UFUNCTION(Server, Reliable, WithValidation)
	void Server_RequestSlotSelectionChange(uint8 NewSlotID);
};
