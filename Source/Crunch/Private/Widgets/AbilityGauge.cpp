// (c)2025 Ravenscroft Productions


#include "Widgets/AbilityGauge.h"

#include "Abilities/GameplayAbility.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "GAS/CAbilitySystemStatics.h"

void UAbilityGauge::NativeConstruct()
{
	Super::NativeConstruct();

	CooldownCounterText->SetVisibility(ESlateVisibility::Hidden);
}

void UAbilityGauge::NativeOnListItemObjectSet(UObject* ListItemObject)
{
	IUserObjectListEntry::NativeOnListItemObjectSet(ListItemObject);
	AbilityCDO = Cast<UGameplayAbility>(ListItemObject);

	float CooldownDuration = UCAbilitySystemStatics::GetStaticCooldownDurationForAbility(AbilityCDO);
	float Cost = UCAbilitySystemStatics::GetStaticCostForAbility(AbilityCDO);

	CostText->SetText(FText::AsNumber(Cost));
	CooldownDurationText->SetText(FText::AsNumber(CooldownDuration));
}

void UAbilityGauge::ConfigureWithWidgetData(const FAbilityWidgetData* WidgetData)
{
	if (Icon && WidgetData)
	{
		Icon->GetDynamicMaterial()->SetTextureParameterValue(IconMaterialParamName, WidgetData->Icon.LoadSynchronous());
	}
}
