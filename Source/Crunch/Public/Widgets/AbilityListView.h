// (c)2025 Ravenscroft Productions

#pragma once

#include "CoreMinimal.h"
#include "Components/ListView.h"
#include "AbilityListView.generated.h"

class UGameplayAbility;
enum class ECAbilityInputID : uint8;
/**
 * 
 */
UCLASS()
class CRUNCH_API UAbilityListView : public UListView
{
	GENERATED_BODY()
public:
	void ConfigureAbilities(const TMap<ECAbilityInputID, TSubclassOf<UGameplayAbility>>& Abilities);

	UPROPERTY(EditAnywhere, Category = "Data")
	UDataTable* AbilityDataTable;

	void AbilityGaugeGenerated(UUserWidget& Widget);

	const struct FAbilityWidgetData* FindWidgetDataForAbility(const TSubclassOf<UGameplayAbility>& AbilityClass) const;
};
