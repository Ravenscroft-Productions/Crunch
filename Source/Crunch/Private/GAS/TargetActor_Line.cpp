// (c)2025 Ravenscroft Productions


#include "GAS/TargetActor_Line.h"

#include "Components/SphereComponent.h"
#include "Crunch/Crunch.h"
#include "NiagaraComponent.h"
#include "Abilities/GameplayAbility.h"
#include "Kismet/KismetMathLibrary.h"
#include "Net/UnrealNetwork.h"

ATargetActor_Line::ATargetActor_Line()
{
	RootComp = CreateDefaultSubobject<USceneComponent>("Root Comp");
	SetRootComponent(RootComp);

	TargetEndDetectionSphere = CreateDefaultSubobject<USphereComponent>("Target End Detection Sphere");
	TargetEndDetectionSphere->SetupAttachment(GetRootComponent());
	TargetEndDetectionSphere->SetCollisionResponseToChannel(ECC_SpringArm, ECR_Ignore);

	LaserVFX = CreateDefaultSubobject<UNiagaraComponent>("LaserVFX");
	LaserVFX->SetupAttachment(GetRootComponent());

	PrimaryActorTick.bCanEverTick = true;
	bReplicates = true;
	ShouldProduceTargetDataOnServer = true;

	AvatarActor = nullptr;
}

void ATargetActor_Line::ConfigureTargetSetting(float NewTargetRange, float NewDetectionCylinderRadius, float NewTargetingInterval, FGenericTeamId OwnerTeamId, bool bShouldDrawDebug)
{
	TargetRange = NewTargetRange;
	DetectionCylinderRadius = NewDetectionCylinderRadius;
	TargetingInterval = NewTargetingInterval;
	SetGenericTeamId(OwnerTeamId);
	bDrawDebug = bShouldDrawDebug;
}

void ATargetActor_Line::SetGenericTeamId(const FGenericTeamId& NewTeamID)
{
	TeamId = NewTeamID;
}

void ATargetActor_Line::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ATargetActor_Line, TeamId);
	DOREPLIFETIME(ATargetActor_Line, TargetRange);
	DOREPLIFETIME(ATargetActor_Line, DetectionCylinderRadius);
	DOREPLIFETIME(ATargetActor_Line, AvatarActor);
}

void ATargetActor_Line::StartTargeting(UGameplayAbility* Ability)
{
	Super::StartTargeting(Ability);
	if (!OwningAbility) return;

	AvatarActor = OwningAbility->GetAvatarActorFromActorInfo();
	if (HasAuthority())
	{
		GetWorldTimerManager().SetTimer(PeriodicalTargetingTimerHandle, this, &ATargetActor_Line::DoTargetCheckAndReport, TargetingInterval, true);
	}
}

void ATargetActor_Line::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	UpdateTargetTrace();
}

void ATargetActor_Line::DoTargetCheckAndReport()
{
	
}

void ATargetActor_Line::UpdateTargetTrace()
{
	FVector ViewLocation = GetActorLocation();
	FRotator ViewRotation = GetActorRotation();
	if (AvatarActor)
	{
		AvatarActor->GetActorEyesViewPoint(ViewLocation, ViewRotation);
	}

	FVector LookEndPoint = ViewLocation + ViewRotation.Vector() * 100000;
	FRotator LookRotation = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), LookEndPoint);
	SetActorRotation(LookRotation);

	FVector SweepEndLocation = GetActorLocation() + LookRotation.Vector() * TargetRange;

	TArray<FHitResult> HitResults;

	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(AvatarActor);
	QueryParams.AddIgnoredActor(this);
	
	FCollisionResponseParams ResponseParams(ECR_Overlap);
	
	GetWorld()->SweepMultiByChannel(HitResults, GetActorLocation(), SweepEndLocation, FQuat::Identity, ECC_WorldDynamic, FCollisionShape::MakeSphere(DetectionCylinderRadius), QueryParams, ResponseParams);

	FVector LineEndLocation = SweepEndLocation;
	float LineLength = TargetRange;

	for (FHitResult& HitResult : HitResults)
	{
		if (HitResult.GetActor())
		{
			if (GetTeamAttitudeTowards(*HitResult.GetActor()) != ETeamAttitude::Friendly)
			{
				LineEndLocation = HitResult.ImpactPoint;
				LineLength = FVector::Distance(GetActorLocation(), LineEndLocation);
			}
		}
	}

	TargetEndDetectionSphere->SetWorldLocation(LineEndLocation);
	if (LaserVFX)
	{
		LaserVFX->SetVariableFloat(LaserFXLengthParamName, LineLength/100);
	}
}
