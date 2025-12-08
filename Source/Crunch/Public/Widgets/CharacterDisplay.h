// (c)2025 Ravenscroft Productions

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CharacterDisplay.generated.h"

class UPA_CharacterDefinition;
class UCameraComponent;

UCLASS()
class CRUNCH_API ACharacterDisplay : public AActor
{
	GENERATED_BODY()
public:
	ACharacterDisplay();
	void ConfigureWithCharacterDefinition(const UPA_CharacterDefinition* CharacterDefinition);
	
private:
	UPROPERTY(VisibleDefaultsOnly, Category = "Character Display")
	USkeletalMeshComponent* MeshComponent;
	
	UPROPERTY(VisibleDefaultsOnly, Category = "Character Display")
	UCameraComponent* ViewCameraComponent;
};
