// (c)2025 Ravenscroft Productions


#include "Framework/StormCore.h"

#include "AIController.h"
#include "GenericTeamAgentInterface.h"
#include "Components/SphereComponent.h"
#include "GameFramework/CharacterMovementComponent.h"


AStormCore::AStormCore()
{
	PrimaryActorTick.bCanEverTick = true;
	InfluenceRange = CreateDefaultSubobject<USphereComponent>("Influence Range");
	InfluenceRange->SetupAttachment(GetRootComponent());

	InfluenceRange->OnComponentBeginOverlap.AddDynamic(this, &AStormCore::NewInfluencerInRange);
	InfluenceRange->OnComponentEndOverlap.AddDynamic(this, &AStormCore::InfluencerLeftRange);
}

void AStormCore::BeginPlay()
{
	Super::BeginPlay();
	
}

void AStormCore::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	OwnerAIC = Cast<AAIController>(NewController);
}

void AStormCore::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AStormCore::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void AStormCore::NewInfluencerInRange(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	IGenericTeamAgentInterface* OtherTeamInterface = Cast<IGenericTeamAgentInterface>(OtherActor);
	if (OtherTeamInterface)
	{
		if (OtherTeamInterface->GetGenericTeamId().GetId() == 0)
		{
			TeamOneInfluencerCount++;
		}
		else if (OtherTeamInterface->GetGenericTeamId().GetId() == 1)
		{
			TeamTwoInfluencerCount++;
		}
		UpdateTeamWeight();
	}
}

void AStormCore::InfluencerLeftRange(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	IGenericTeamAgentInterface* OtherTeamInterface = Cast<IGenericTeamAgentInterface>(OtherActor);
	if (OtherTeamInterface)
	{
		if (OtherTeamInterface->GetGenericTeamId().GetId() == 0)
		{
			TeamOneInfluencerCount--;
			if (TeamOneInfluencerCount < 0)
			{
				TeamOneInfluencerCount = 0;
			}
		}
		else if (OtherTeamInterface->GetGenericTeamId().GetId() == 1)
		{
			TeamTwoInfluencerCount--;
			if (TeamTwoInfluencerCount < 0)
			{
				TeamTwoInfluencerCount = 0;
			}
		}
		UpdateTeamWeight();
	}
}

void AStormCore::UpdateTeamWeight()
{
	if (TeamOneInfluencerCount == TeamTwoInfluencerCount)
	{
		TeamWeight = 0.0f;
	}
	else
	{
		float TeamOffset = TeamOneInfluencerCount - TeamTwoInfluencerCount;
		float TeamTotal = TeamOneInfluencerCount + TeamTwoInfluencerCount;
		TeamWeight = TeamOffset / TeamTotal;
	}

	UE_LOG(LogTemp, Warning, TEXT("Team One Count: %d, Team Two Count: %d, Weight: %f"), TeamOneInfluencerCount, TeamTwoInfluencerCount, TeamWeight);
	UpdateGoal();
}

void AStormCore::UpdateGoal()
{
	if (!HasAuthority()) return;

	if (!OwnerAIC) return;

	if (!GetCharacterMovement()) return;

	if (TeamWeight > 0.0f)
	{
		OwnerAIC->MoveToActor(TeamOneGoal);
	}
	else
	{
		OwnerAIC->MoveToActor(TeamTwoGoal);
	}

	float Speed = MaxMoveSpeed * FMath::Abs(TeamWeight);

	GetCharacterMovement()->MaxWalkSpeed = Speed;
}

