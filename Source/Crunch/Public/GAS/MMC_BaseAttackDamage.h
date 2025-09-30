// (c)2025 Ravenscroft Productions

#pragma once

#include "CoreMinimal.h"
#include "GameplayModMagnitudeCalculation.h"
#include "MMC_BaseAttackDamage.generated.h"

/**
 * 
 */
UCLASS()
class CRUNCH_API UMMC_BaseAttackDamage : public UGameplayModMagnitudeCalculation
{
	GENERATED_BODY()
public:
	UMMC_BaseAttackDamage();
	virtual float CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const override;

private:
	FGameplayEffectAttributeCaptureDefinition DamageCaptureDef;
	FGameplayEffectAttributeCaptureDefinition ArmourCaptureDef;
};
