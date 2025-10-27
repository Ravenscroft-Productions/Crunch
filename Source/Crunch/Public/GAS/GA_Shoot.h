// (c)2025 Ravenscroft Productions

#pragma once

#include "CoreMinimal.h"
#include "CGameplayAbility.h"
#include "GA_Shoot.generated.h"

/**
 * 
 */
UCLASS()
class CRUNCH_API UGA_Shoot : public UCGameplayAbility
{
	GENERATED_BODY()
public:
	UGA_Shoot();
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
	virtual void InputReleased(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo) override;
	
private:
	UPROPERTY(EditDefaultsOnly, Category = "Animation")
	UAnimMontage* ShootMontage;
	
	static FGameplayTag GetShootTag();
	
	UFUNCTION()
	void StartShooting(FGameplayEventData Payload);

	UFUNCTION()
	void StopShooting(FGameplayEventData Payload);

	UFUNCTION()
	void ShootProjectile(FGameplayEventData Payload);
};
