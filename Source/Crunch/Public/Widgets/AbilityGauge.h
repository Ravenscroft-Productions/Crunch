// (c)2025 Ravenscroft Productions

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "AbilityGauge.generated.h"

class UTextBlock;
class UImage;
/**
 * 
 */
UCLASS()
class CRUNCH_API UAbilityGauge : public UUserWidget
{
	GENERATED_BODY()
private:
	UPROPERTY(meta = (BindWidget))
	UImage* Icon;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* CooldownCounterText;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* CooldownDurationText;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* CostText;
};	
