// (c)2025 Ravenscroft Productions

#pragma once

#include "CoreMinimal.h"
#include "CGameplayAbility.h"
#include "GA_Tornado.generated.h"

/**
 * 
 */
UCLASS()
class CRUNCH_API UGA_Tornado : public UCGameplayAbility
{
	GENERATED_BODY()
public:
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
	
private:
	UPROPERTY(EditDefaultsOnly, Category = "Effect")
	TSubclassOf<UGameplayEffect> HitDamageEffect;
	
	UPROPERTY(EditDefaultsOnly, Category = "Effect")
	float HitPushSpeed = 3000.0f;
	
	UPROPERTY(EditDefaultsOnly, Category = "Anim")
	UAnimMontage* TornadoMontage;
	
	UPROPERTY(EditDefaultsOnly, Category = "Effect")
	float TornadoDuration = 4.0f;
	
	UFUNCTION()
	void TornadoDamageEventReceived(FGameplayEventData Payload);
};
