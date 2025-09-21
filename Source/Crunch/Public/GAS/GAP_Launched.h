// (c)2025 Ravenscroft Productions

#pragma once

#include "CoreMinimal.h"
#include "CGameplayAbility.h"
#include "GAP_Launched.generated.h"

/**
 * 
 */
UCLASS()
class CRUNCH_API UGAP_Launched : public UCGameplayAbility
{
	GENERATED_BODY()
public:
	UGAP_Launched();
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
	static FGameplayTag GetLaunchedAbilityActivationTag();
};
