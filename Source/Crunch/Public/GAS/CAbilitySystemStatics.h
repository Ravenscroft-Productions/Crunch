// (c)2025 Ravenscroft Productions

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "CAbilitySystemStatics.generated.h"

class UGameplayAbility;
/**
 * 
 */
UCLASS()
class CRUNCH_API UCAbilitySystemStatics : public UObject
{
	GENERATED_BODY()
public:
	static FGameplayTag GetBasicAttackAbilityTag();
	static FGameplayTag GetDeadStatTag();
	static FGameplayTag GetStunStatTag();
	static FGameplayTag GetBasicAttackInputPressedTag();
	static FGameplayTag GetAimStatTag();
	static FGameplayTag GetCameraShakeGameplayCueTag();
	static FGameplayTag GetHealthFullStatTag();
	static FGameplayTag GetHealthEmptyStatTag();
	static FGameplayTag GetManaFullStatTag();
	static FGameplayTag GetManaEmptyStatTag();
	static FGameplayTag GetHeroRoleTag();
	static bool IsHero(const AActor* ActorToCheck);

	static float GetStaticCooldownDurationForAbility(const UGameplayAbility* Ability);
	static float GetStaticCostForAbility(const UGameplayAbility* Ability);
};
