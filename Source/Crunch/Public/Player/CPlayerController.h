// (c)2025 Ravenscroft Productions

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "CPlayerController.generated.h"

class ACPlayerCharacter;
/**
 * 
 */
UCLASS()
class CRUNCH_API ACPlayerController : public APlayerController
{
	GENERATED_BODY()
public:
	// Only called on the server
	void OnPossess(APawn* NewPawn) override;

	// Only called on the client, also on the listening server.
	void AcknowledgePossession(APawn* NewPawn) override;

private:
	UPROPERTY()
	ACPlayerCharacter* CPlayerCharacter;
};
