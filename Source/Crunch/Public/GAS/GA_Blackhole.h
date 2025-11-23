// (c)2025 Ravenscroft Productions

#pragma once

#include "CoreMinimal.h"
#include "CGameplayAbility.h"
#include "GA_Blackhole.generated.h"

class UAbilityTask_WaitTargetData;
class ATA_Blackhole;
class UAbilityTask_PlayMontageAndWait;
class ATargetActor_GroundPick;
/**
 * 
 */
UCLASS()
class CRUNCH_API UGA_Blackhole : public UCGameplayAbility
{
	GENERATED_BODY()
public:
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;	
	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;
		
private:
	UPROPERTY(EditDefaultsOnly, Category = "Targeting")
	float TargetAreaRadius = 1000.0f;
	
	UPROPERTY(EditDefaultsOnly, Category = "Targeting")
	float BlackholePullSpeed = 3000.0f;
	
	UPROPERTY(EditDefaultsOnly, Category = "Targeting")
	float BlackholeDuration = 6.0f;
	
	UPROPERTY(EditDefaultsOnly, Category = "Targeting")
	float TargetTraceRange = 2000.0f;
	
	UPROPERTY(EditDefaultsOnly, Category = "Animation")
	UAnimMontage* TargetingMontage;
	
	UPROPERTY(EditDefaultsOnly, Category = "Animation")
	UAnimMontage* HoldBlackholeMontage;
	
	UPROPERTY(EditDefaultsOnly, Category = "Animation")
	UAnimMontage* FinalBlowMontage;
	
	UPROPERTY(EditDefaultsOnly, Category = "Targeting")
	TSubclassOf<UGameplayEffect> AimEffect;
	
	FActiveGameplayEffectHandle AimEffectHandle;
	
	UPROPERTY(EditDefaultsOnly, Category = "Targeting")
	TSubclassOf<ATargetActor_GroundPick> TargetActorClass;
	
	UPROPERTY(EditDefaultsOnly, Category = "Targeting")
	TSubclassOf<ATA_Blackhole> BlackholeTargetActorClass;
	
	UPROPERTY(EditDefaultsOnly, Category = "Effect")
	TSubclassOf<UGameplayEffect> FinalBlowDamageEffect;
	
	UPROPERTY(EditDefaultsOnly, Category = "Effect")
	float BlowPushSpeed = 3000.0f;
	
	UPROPERTY()
	UAbilityTask_PlayMontageAndWait* PlayCastBlackholeMontageTask;
	
	UPROPERTY()
	UAbilityTask_WaitTargetData* BlackholeTargetingTask;
	
	UFUNCTION()
	void PlaceBlackhole(const FGameplayAbilityTargetDataHandle& TargetDataHandle);
	
	UFUNCTION()
	void PlacementCancelled(const FGameplayAbilityTargetDataHandle& TargetDataHandle);
	
	UFUNCTION()
	void FinalTargetReceived(const FGameplayAbilityTargetDataHandle& TargetDataHandle);
	
	void AddAimEffect();
	void RemoveAimEffect();
};
