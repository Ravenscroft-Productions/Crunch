// (c)2025 Ravenscroft Productions

#pragma once

#include "CoreMinimal.h"
#include "GameplayModMagnitudeCalculation.h"
#include "MMC_LevelBased.generated.h"

/**
 * 
 */
UCLASS()
class CRUNCH_API UMMC_LevelBased : public UGameplayModMagnitudeCalculation
{
	GENERATED_BODY()
public:
	UMMC_LevelBased();

	float CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const override;

private:
	UPROPERTY(EditDefaultsOnly)
	FGameplayAttribute RateAttribute;

	FGameplayEffectAttributeCaptureDefinition LevelCaptureDefinition;
};
