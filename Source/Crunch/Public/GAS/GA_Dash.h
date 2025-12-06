// (c)2025 Ravenscroft Productions

#pragma once

#include "CoreMinimal.h"
#include "CGameplayAbility.h"
#include "GA_Dash.generated.h"

class UCharacterMovementComponent;
class ATargetActor_Around;
/**
 * 
 */
UCLASS()
class CRUNCH_API UGA_Dash : public UCGameplayAbility
{
	GENERATED_BODY()
public:
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;
	
	static FGameplayTag GetDashStartTag();
	
private:
	UPROPERTY(EditDefaultsOnly, Category = "Anim")
	UAnimMontage* DashMontage;
	
	UPROPERTY(EditDefaultsOnly, Category = "Targeting")
	float TargetDetectionRadius = 300.0f;
	
	UPROPERTY(EditDefaultsOnly, Category = "GameplayCue")
	FGameplayTag LocalGameplayCueTag;
	
	UPROPERTY(EditDefaultsOnly, Category = "Targeting")
	FName TargetActorAttachSocketName = "TargetDashCenter";
	
	UPROPERTY(EditDefaultsOnly, Category = "Targeting")
	TSubclassOf<ATargetActor_Around> TargetActorClass;
	
	UPROPERTY(EditDefaultsOnly, Category = "Effects")
	float TargetHitPushSpeed = 3000.0f;
	
	UPROPERTY(EditDefaultsOnly, Category = "Effects")
	TSubclassOf<UGameplayEffect> DamageEffect;
	
	UPROPERTY(EditDefaultsOnly, Category = "Effects")
	TSubclassOf<UGameplayEffect> DashEffect;
	
	FActiveGameplayEffectHandle DashEffectHandle;
	
	FTimerHandle PushForwardInputTimerHandle;
	
	void PushForward();
	UCharacterMovementComponent* OwnerCharacterMovementComponent;
	
	UFUNCTION()
	void StartDash(FGameplayEventData Payload);
	
	UFUNCTION()
	void TargetReceived(const FGameplayAbilityTargetDataHandle& TargetDataHandle);
};