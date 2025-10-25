// (c)2025 Ravenscroft Productions

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "StormCore.generated.h"

class AAIController;
class USphereComponent;

UCLASS()
class CRUNCH_API AStormCore : public ACharacter
{
	GENERATED_BODY()

public:
	AStormCore();

protected:
	virtual void BeginPlay() override;
	virtual void PossessedBy(AController* NewController) override;

public:
	virtual void Tick(float DeltaTime) override;
	
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	UPROPERTY(EditDefaultsOnly, Category = "Move")
	float MaxMoveSpeed = 500.0f;
	
	UPROPERTY(VisibleDefaultsOnly, Category = "Detection")
	USphereComponent* InfluenceRange;

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
	
	int TeamOneInfluencerCount = 0;
	int TeamTwoInfluencerCount = 0;

	float TeamWeight = 0.0f;

	UPROPERTY()
	AAIController* OwnerAIC;
};
