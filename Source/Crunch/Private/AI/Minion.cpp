// (c)2025 Ravenscroft Productions


#include "AI/Minion.h"

#include "AbilitySystemComponent.h"
#include "GAS/CAbilitySystemStatics.h"

void AMinion::SetGenericTeamId(const FGenericTeamId& NewTeamID)
{
	Super::SetGenericTeamId(NewTeamID);
	PickSkinBasedOnTeamID();
}

bool AMinion::IsActive() const
{
	return !GetAbilitySystemComponent()->HasMatchingGameplayTag(UCAbilitySystemStatics::GetDeadStatTag());
}

void AMinion::Activate()
{
	GetAbilitySystemComponent()->RemoveActiveEffectsWithGrantedTags(FGameplayTagContainer(UCAbilitySystemStatics::GetDeadStatTag()));
}

void AMinion::PickSkinBasedOnTeamID()
{
	USkeletalMesh** Skin = SkinMap.Find(GetGenericTeamId());
	if (Skin)
	{
		GetMesh()->SetSkeletalMesh(*Skin);
	}
}

void AMinion::OnRep_TeamID()
{
	PickSkinBasedOnTeamID();
}
