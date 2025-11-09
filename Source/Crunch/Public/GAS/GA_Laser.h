// (c)2025 Ravenscroft Productions

#pragma once

#include "CoreMinimal.h"
#include "CGameplayAbility.h"
#include "GA_Laser.generated.h"

class ATargetActor_Line;
/**
 * 
 */
UCLASS()
class CRUNCH_API UGA_Laser : public UCGameplayAbility
{
	GENERATED_BODY()
public:
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;
	static FGameplayTag GetShootTag();
	
private:
	UPROPERTY(EditDefaultsOnly, Category = "Targeting")
	float TargetRange = 4000.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Targeting")
	float DetectionCylinderRadius = 30.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Targeting")
	float TargetingInterval = 0.3f;
	
	UPROPERTY(EditDefaultsOnly, Category = "Effects")
	TSubclassOf<UGameplayEffect> OnGoingConsumptionEffect;

	FActiveGameplayEffectHandle OnGoingConsumptionEffectHandle;

	UPROPERTY(EditDefaultsOnly, Category = "Anim")
	UAnimMontage* LaserMontage;

	UPROPERTY(EditDefaultsOnly, Category = "Targeting")
	FName TargetActorAttachSocketName = "Laser";

	UPROPERTY(EditDefaultsOnly, Category = "Targeting")
	TSubclassOf<ATargetActor_Line> LaserTargetActorClass;
	
	UFUNCTION()
	void ShootLaser(FGameplayEventData Payload);

	void ManaUpdated(const FOnAttributeChangeData& ChangeData);

	UFUNCTION()
	void TargetReceived(const FGameplayAbilityTargetDataHandle& TargetDataHandle);
};
