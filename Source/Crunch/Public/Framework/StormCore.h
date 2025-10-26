// (c)2025 Ravenscroft Productions

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "StormCore.generated.h"

DECLARE_MULTICAST_DELEGATE_TwoParams(FOnGoalReachedDelegate, AActor* /*ViewTarget*/, int /*WiningTeam*/);
DECLARE_MULTICAST_DELEGATE_TwoParams(FOnTeamInfluencerCountUpdatedDelegate, int /*TeamOneInfluencerCount*/, int /*TeamTwoInfluencerCount*/);

class UCameraComponent;
class AAIController;
class USphereComponent;

UCLASS()
class CRUNCH_API AStormCore : public ACharacter
{
	GENERATED_BODY()

public:
	FOnGoalReachedDelegate OnGoalReached;
	FOnTeamInfluencerCountUpdatedDelegate OnTeamInfluencerCountUpdated;
	
	AStormCore();
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	float GetProgress() const;

protected:
	virtual void BeginPlay() override;
	virtual void PossessedBy(AController* NewController) override;

public:
	virtual void Tick(float DeltaTime) override;
	
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;

private:
	UPROPERTY(EditDefaultsOnly, Category = "Move")
	UAnimMontage* ExpandMontage;

	UPROPERTY(EditDefaultsOnly, Category = "Move")
	UAnimMontage* CaptureMontage;
	
	UPROPERTY(EditDefaultsOnly, Category = "Move")
	float InfluenceRadius = 1000.0f;
	
	UPROPERTY(EditDefaultsOnly, Category = "Move")
	float MaxMoveSpeed = 500.0f;
	
	UPROPERTY(VisibleDefaultsOnly, Category = "Detection")
	USphereComponent* InfluenceRange;
	
	UPROPERTY(VisibleDefaultsOnly, Category = "Detection")
	UDecalComponent* GroundDecalComponent;

	UPROPERTY(VisibleDefaultsOnly, Category = "Detection")
	UCameraComponent* ViewCam;

	UFUNCTION()
	void NewInfluencerInRange(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void InfluencerLeftRange(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	void UpdateTeamWeight();
	void UpdateGoal();

	UPROPERTY(EditAnywhere, Category = "Team")
	AActor* TeamOneGoal;

	UPROPERTY(EditAnywhere, Category = "Team")
	AActor* TeamTwoGoal;

	UPROPERTY(EditAnywhere, Category = "Team")
	AActor* TeamOneCore;

	UPROPERTY(EditAnywhere, Category = "Team")
	AActor* TeamTwoCore;

	UPROPERTY(ReplicatedUsing = OnRep_CoreToCapture)
	AActor* CoreToCapture;

	float CoreCaptureSpeed = 0.0f;
	float TravelLength = 0.0f;

	UFUNCTION()
	void OnRep_CoreToCapture();

	void GoalReached(int WiningTeam);

	void CaptureCore();
	void ExpandFinished();
	
	int TeamOneInfluencerCount = 0;
	int TeamTwoInfluencerCount = 0;

	float TeamWeight = 0.0f;

	UPROPERTY()
	AAIController* OwnerAIC;
};
