// (c)2025 Ravenscroft Productions

#pragma once

#include "CoreMinimal.h"
#include "CGameplayAbility.h"
#include "GA_GroundBlast.generated.h"

class ATargetActor_GroundPick;
/**
 * 
 */
UCLASS()
class CRUNCH_API UGA_GroundBlast : public UCGameplayAbility
{
	GENERATED_BODY()

public:
	UGA_GroundBlast();
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;

private:
	UPROPERTY(EditDefaultsOnly, Category = "Targeting")
	TSubclassOf<ATargetActor_GroundPick> TargetActorClass;
	
	UPROPERTY(EditDefaultsOnly, Category = "Animation")
	UAnimMontage* GroundBlastMontage;

	UFUNCTION()
	void TargetConfirmed(const FGameplayAbilityTargetDataHandle& TargetDataHandle);

	UFUNCTION()
	void TargetCancelled(const FGameplayAbilityTargetDataHandle& TargetDataHandle);
};
