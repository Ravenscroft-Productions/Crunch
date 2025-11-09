// (c)2025 Ravenscroft Productions


#include "GAS/GA_Laser.h"

#include "AbilitySystemComponent.h"
#include "Abilities/Tasks/AbilityTask_PlayMontageAndWait.h"
#include "Abilities/Tasks/AbilityTask_WaitGameplayEvent.h"
#include "Abilities/Tasks/AbilityTask_WaitCancel.h"
#include "Abilities/Tasks/AbilityTask_WaitTargetData.h"
#include "GAS/CAttributeSet.h"
#include "Gas/TargetActor_Line.h"

void UGA_Laser::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	if (!K2_CommitAbility() || !LaserMontage)
	{
		K2_EndAbility();
		return;
	}

	if (HasAuthorityOrPredictionKey(ActorInfo, &ActivationInfo))
	{
		UAbilityTask_PlayMontageAndWait* PlayLaserMontageTask = UAbilityTask_PlayMontageAndWait::CreatePlayMontageAndWaitProxy(this, NAME_None, LaserMontage);
		PlayLaserMontageTask->OnBlendOut.AddDynamic(this, &UGA_Laser::K2_EndAbility);
		PlayLaserMontageTask->OnCancelled.AddDynamic(this, &UGA_Laser::K2_EndAbility);
		PlayLaserMontageTask->OnCompleted.AddDynamic(this, &UGA_Laser::K2_EndAbility);
		PlayLaserMontageTask->OnInterrupted.AddDynamic(this, &UGA_Laser::K2_EndAbility);
		PlayLaserMontageTask->ReadyForActivation();

		UAbilityTask_WaitGameplayEvent* WaitShootEvent = UAbilityTask_WaitGameplayEvent::WaitGameplayEvent(this, GetShootTag());
		WaitShootEvent->EventReceived.AddDynamic(this, &UGA_Laser::ShootLaser);
		WaitShootEvent->ReadyForActivation();

		UAbilityTask_WaitCancel* WaitCancel = UAbilityTask_WaitCancel::WaitCancel(this);
		WaitCancel->OnCancel.AddDynamic(this, &UGA_Laser::K2_EndAbility);
		WaitCancel->ReadyForActivation();
	}
}

void UGA_Laser::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	UAbilitySystemComponent* OwnerAbilitySystemComponent = GetAbilitySystemComponentFromActorInfo();
	if (OwnerAbilitySystemComponent && OnGoingConsumptionEffectHandle.IsValid())
	{
		OwnerAbilitySystemComponent->RemoveActiveGameplayEffect(OnGoingConsumptionEffectHandle);
	}

	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}

FGameplayTag UGA_Laser::GetShootTag()
{
	return FGameplayTag::RequestGameplayTag("Ability.Laser.Shoot");
}

void UGA_Laser::ShootLaser(FGameplayEventData Payload)
{
	if (K2_HasAuthority())
	{
		OnGoingConsumptionEffectHandle = BP_ApplyGameplayEffectToOwner(OnGoingConsumptionEffect, GetAbilityLevel(CurrentSpecHandle, CurrentActorInfo));
		UAbilitySystemComponent* OwnerAbilitySystemComponent = GetAbilitySystemComponentFromActorInfo();
		if (OwnerAbilitySystemComponent)
		{
			OwnerAbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(UCAttributeSet::GetManaAttribute()).AddUObject(this, &UGA_Laser::ManaUpdated);
		}
	}	

	UAbilityTask_WaitTargetData* WaitDamageTargetTask = UAbilityTask_WaitTargetData::WaitTargetData(this, NAME_None, EGameplayTargetingConfirmation::CustomMulti, LaserTargetActorClass);
	WaitDamageTargetTask->ValidData.AddDynamic(this, &UGA_Laser::TargetReceived);
	WaitDamageTargetTask->ReadyForActivation();

	AGameplayAbilityTargetActor* TargetActor;
	WaitDamageTargetTask->BeginSpawningActor(this, LaserTargetActorClass, TargetActor);
	WaitDamageTargetTask->FinishSpawningActor(this, TargetActor);

	ATargetActor_Line* LineTargetActor = Cast<ATargetActor_Line>(TargetActor);
	if (LineTargetActor)
	{
		LineTargetActor->ConfigureTargetSetting(TargetRange, DetectionCylinderRadius, TargetingInterval, GetOwnerTeamId(), ShouldDrawDebug());
		LineTargetActor->AttachToComponent(GetOwningComponentFromActorInfo(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, TargetActorAttachSocketName);
	}
}

void UGA_Laser::ManaUpdated(const FOnAttributeChangeData& ChangeData)
{
	UAbilitySystemComponent* OwnerAbilitySystemComponent = GetAbilitySystemComponentFromActorInfo();
	if (OwnerAbilitySystemComponent && !OwnerAbilitySystemComponent->CanApplyAttributeModifiers(OnGoingConsumptionEffect.GetDefaultObject(), GetAbilityLevel(CurrentSpecHandle, CurrentActorInfo), MakeEffectContext(CurrentSpecHandle, CurrentActorInfo)))
	{
		K2_EndAbility();
	}
}

void UGA_Laser::TargetReceived(const FGameplayAbilityTargetDataHandle& TargetDataHandle)
{	
}
