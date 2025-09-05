// (c)2025 Ravenscroft Productions

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "CAbilitySystemComponent.generated.h"

/**
 * 
 */
UCLASS()
class CRUNCH_API UCAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()
public:
	void ApplyInitialEffects();
	
private:
	TArray<TSubclassOf<UGameplayEffect>> InitialEffects;
};
