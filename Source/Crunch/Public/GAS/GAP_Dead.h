// (c)2025 Ravenscroft Productions

#pragma once

#include "CoreMinimal.h"
#include "CGameplayAbility.h"
#include "GAP_Dead.generated.h"

/**
 * 
 */
UCLASS()
class CRUNCH_API UGAP_Dead : public UCGameplayAbility
{
	GENERATED_BODY()
public:
	UGAP_Dead();
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;

private:
	UPROPERTY(EditDefaultsOnly, Category = "Reward")
	float RewardRange = 1000.0f;

	TArray<AActor*> GetRewardTargets() const;
};
