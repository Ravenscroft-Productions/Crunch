// (c)2025 Ravenscroft Productions

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameplayWidget.generated.h"

class UMatchStatWidget;
class USkeletalMeshRenderWidget;
class UInventoryWidget;
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

	UPROPERTY(meta=(BindWidget))
	UInventoryWidget* InventoryWidget;

	UPROPERTY(meta=(BindWidget))
	USkeletalMeshRenderWidget* HeadShotWidget;

	UPROPERTY(meta=(BindWidget))
	UMatchStatWidget* MatchStatWidget;

	UPROPERTY(Transient, meta= (BindWidgetAnim))
	UWidgetAnimation* ShopPopupAnimation;

	void PlayShopPopupAnimation(bool bPlayForward);
	void SetOwningPawnInputEnabled(bool bPawnInputEnabled);
	void SetShowMouseCursor(bool bShowMouseCursor);
	void SetFocusToGameAndUI();
	void SetFocusToGameOnly();
	
	UPROPERTY()
	UAbilitySystemComponent* OwnerAbilitySystemComponent;
};
