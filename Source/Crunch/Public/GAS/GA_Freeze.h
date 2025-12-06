// (c)2025 Ravenscroft Productions

#pragma once

#include "CoreMinimal.h"
#include "CGameplayAbility.h"
#include "GA_Freeze.generated.h"

class ATargetActor_GroundPick;
/**
 * 
 */
UCLASS()
class CRUNCH_API UGA_Freeze : public UCGameplayAbility
{
	GENERATED_BODY()
public:
	UGA_Freeze();
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
	
private:
	UPROPERTY(EditDefaultsOnly, Category = "Targeting")
	float TargetingRadius = 1000.0f;
	
	UPROPERTY(EditDefaultsOnly, Category = "Targeting")
	float TargetRange = 2000.0f;
	
	UPROPERTY(EditDefaultsOnly, Category = "Targeting")
	TSubclassOf<ATargetActor_GroundPick> TargetActorClass;
	
	UPROPERTY(EditDefaultsOnly, Category = "Animation")
	UAnimMontage* FreezeTargetingMontage;
	
	UPROPERTY(EditDefaultsOnly, Category = "Animation")
	UAnimMontage* FreezeCastMontage;
	
	UPROPERTY(EditDefaultsOnly, Category = "Effect")
	TSubclassOf<UGameplayEffect> DamageEffect;
	
	UPROPERTY(EditDefaultsOnly, Category = "GameplayCue")
	FGameplayTag FreezingTargetGameplayCueTag;
	
	UPROPERTY(EditDefaultsOnly, Category = "GameplayCue")
	FGameplayTag FreezingGameplayCueTag;
	
	UFUNCTION()
	void TargetReceived(const FGameplayAbilityTargetDataHandle& TargetDataHandle);
	
	UFUNCTION()
	void TargetingCancelled(const FGameplayAbilityTargetDataHandle& TargetDataHandle);
};
