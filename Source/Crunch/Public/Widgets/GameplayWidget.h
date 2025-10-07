// (c)2025 Ravenscroft Productions

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameplayWidget.generated.h"

class UShopWidget;
class UStatsGauge;
class UAbilityListView;
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
	void ToggleShop();
	
private:
	UPROPERTY(meta=(BindWidget))
	UValueGauge* HealthBar;

	UPROPERTY(meta=(BindWidget))
	UValueGauge* ManaBar;
	
	UPROPERTY(meta=(BindWidget))
	UAbilityListView* AbilityListView;

	UPROPERTY(meta=(BindWidget))
	UStatsGauge* AttackDamageGauge;

	UPROPERTY(meta=(BindWidget))
	UStatsGauge* ArmourGauge;

	UPROPERTY(meta=(BindWidget))
	UStatsGauge* MoveSpeedGauge;

	UPROPERTY(meta=(BindWidget))
	UStatsGauge* IntelligenceGauge;

	UPROPERTY(meta=(BindWidget))
	UStatsGauge* StrengthGauge;

	UPROPERTY(meta=(BindWidget))
	UShopWidget* ShopWidget;

	UPROPERTY(Transient, meta= (BindWidgetAnim))
	UWidgetAnimation* ShopPopupAnimation;

	void PlayShopPopupAnimation(bool bPlayForward);
	
	UPROPERTY()
	UAbilitySystemComponent* OwnerAbilitySystemComponent;
};
