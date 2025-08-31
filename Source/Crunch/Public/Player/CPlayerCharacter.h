// (c)2025 Ravenscroft Productions

#pragma once

#include "CoreMinimal.h"
#include "Character/CCharacter.h"
#include "CPlayerCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
/**
 * 
 */
UCLASS()
class CRUNCH_API ACPlayerCharacter : public ACCharacter
{
	GENERATED_BODY()
public:
	ACPlayerCharacter();
	
private:
	UPROPERTY(VisibleDefaultsOnly, Category = "View")
	USpringArmComponent* CameraBoom;

	UPROPERTY(VisibleDefaultsOnly, Category = "View")
	UCameraComponent* ViewCam;
};