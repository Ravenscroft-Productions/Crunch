// (c)2025 Ravenscroft Productions

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameplayWidget.generated.h"

enum class ECAbilityInputID : uint8;
class UGameplayAbility;
class UAbilitySystemComponent;
class UValueGauge;
/**
 * 
 */
UCLASS()
class CRUNCH_API UGameplayWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	virtual void NativeConstruct() override;
	void ConfigureAbilities(const TMap<ECAbilityInputID, TSubclassOf<UGameplayAbility>>& Abilities);
	
private:
	UPROPERTY(meta=(BindWidget))
	UValueGauge* HealthBar;

	UPROPERTY(meta=(BindWidget))
	UValueGauge* ManaBar;

	UPROPERTY()
	UAbilitySystemComponent* OwnerAbilitySystemComponent;
};
