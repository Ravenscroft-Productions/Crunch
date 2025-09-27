// (c)2025 Ravenscroft Productions


#include "GAS/GA_GroundBlast.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "Abilities/Tasks/AbilityTask_PlayMontageAndWait.h"
#include "Abilities/Tasks/AbilityTask_WaitTargetData.h"
#include "GAS/CAbilitySystemStatics.h"
#include "GAS/CGameplayAbilityTypes.h"
#include "GAS/TargetActor_GroundPick.h"

UGA_GroundBlast::UGA_GroundBlast()
{
	ActivationOwnedTags.AddTag(UCAbilitySystemStatics::GetAimStatTag());
	BlockAbilitiesWithTag.AddTag(UCAbilitySystemStatics::GetBasicAttackAbilityTag());
}

void UGA_GroundBlast::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	if (!HasAuthorityOrPredictionKey(CurrentActorInfo, &CurrentActivationInfo)) return;

	UAbilityTask_PlayMontageAndWait* PlayGroundBlastAnimTask = UAbilityTask_PlayMontageAndWait::CreatePlayMontageAndWaitProxy(this, NAME_None, GroundBlastMontage);
	PlayGroundBlastAnimTask->OnBlendOut.AddDynamic(this, &UGA_GroundBlast::K2_EndAbility);
	PlayGroundBlastAnimTask->OnCancelled.AddDynamic(this, &UGA_GroundBlast::K2_EndAbility);
	PlayGroundBlastAnimTask->OnInterrupted.AddDynamic(this, &UGA_GroundBlast::K2_EndAbility);
	PlayGroundBlastAnimTask->OnCompleted.AddDynamic(this, &UGA_GroundBlast::K2_EndAbility);
	PlayGroundBlastAnimTask->ReadyForActivation();

	UAbilityTask_WaitTargetData* WaitTargetDataTask = UAbilityTask_WaitTargetData::WaitTargetData(this, NAME_None, EGameplayTargetingConfirmation::UserConfirmed, TargetActorClass);
	WaitTargetDataTask->ValidData.AddDynamic(this, &UGA_GroundBlast::TargetConfirmed);
	WaitTargetDataTask->Cancelled.AddDynamic(this, &UGA_GroundBlast::TargetCancelled);
	WaitTargetDataTask->ReadyForActivation();

	AGameplayAbilityTargetActor* TargetActor; 
	WaitTargetDataTask->BeginSpawningActor(this, TargetActorClass, TargetActor);
	ATargetActor_GroundPick* GroundPickActor = Cast<ATargetActor_GroundPick>(TargetActor);
	if (GroundPickActor)
	{
		GroundPickActor->SetShouldDrawDebug(ShouldDrawDebug());
		GroundPickActor->SetTargetAreaRadius(TargetAreaRadius);
		GroundPickActor->SetTargetTraceRange(TargetTraceRange);
	}
	
	WaitTargetDataTask->FinishSpawningActor(this, TargetActor);
}

void UGA_GroundBlast::TargetConfirmed(const FGameplayAbilityTargetDataHandle& TargetDataHandle)
{
	BP_ApplyGameplayEffectToTarget(TargetDataHandle, DamageEffectDef.DamageEffect, GetAbilityLevel(CurrentSpecHandle, CurrentActorInfo));
	PushTargets(TargetDataHandle, DamageEffectDef.PushVelocity);

	FGameplayCueParameters BlastingGameplayCueParams;
	BlastingGameplayCueParams.Location = UAbilitySystemBlueprintLibrary::GetHitResultFromTargetData(TargetDataHandle, 1).ImpactPoint;
	BlastingGameplayCueParams.RawMagnitude = TargetAreaRadius;

	GetAbilitySystemComponentFromActorInfo()->ExecuteGameplayCue(BlastGameplayCueTag, BlastingGameplayCueParams);
	GetAbilitySystemComponentFromActorInfo()->ExecuteGameplayCue(UCAbilitySystemStatics::GetCameraShakeGameplayCueTag(), BlastingGameplayCueParams);
	
	K2_EndAbility();
}

void UGA_GroundBlast::TargetCancelled(const FGameplayAbilityTargetDataHandle& TargetDataHandle)
{
	K2_EndAbility();
}
