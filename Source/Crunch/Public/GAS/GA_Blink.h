// (c)2025 Ravenscroft Productions

#pragma once

#include "CoreMinimal.h"
#include "CGameplayAbility.h"
#include "GA_Blink.generated.h"

class ATargetActor_GroundPick;
/**
 * 
 */
UCLASS()
class CRUNCH_API UGA_Blink : public UCGameplayAbility
{
	GENERATED_BODY()
public:
	UGA_Blink();
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
	static FGameplayTag GetTeleportationTag();
	
private:
	UPROPERTY(EditDefaultsOnly, Category = "Anim")
	UAnimMontage* TargetingMontage;
	
	UPROPERTY(EditDefaultsOnly, Category = "Anim")
	UAnimMontage* TeleportMontage;
	
	UPROPERTY(EditDefaultsOnly, Category = "Targeting")
	TSubclassOf<ATargetActor_GroundPick> GroundPickTargetActorClass;
	
	UPROPERTY(EditDefaultsOnly, Category = "Effect")
	TSubclassOf<UGameplayEffect> DamageEffect;
	
	UPROPERTY(EditDefaultsOnly, Category = "Effect")
	float BlinkLandTargetPushSpeed = 5000.0f;
	
	UPROPERTY(EditDefaultsOnly, Category = "Targeting")
	float TargetAreaRadius = 1000.0f;
	
	UPROPERTY(EditDefaultsOnly, Category = "Targeting")
	float BlinkCastRange = 3000.0f;
	
	UFUNCTION()
	void GroundPickTargetReceived(const FGameplayAbilityTargetDataHandle& TargetDataHandle);
	
	UFUNCTION()
	void GroundPickCancelled(const FGameplayAbilityTargetDataHandle& TargetDataHandle);
	
	UFUNCTION()
	void Teleport(FGameplayEventData Payload);
	
	FGameplayAbilityTargetDataHandle BlinkTargetDataHandle;
};