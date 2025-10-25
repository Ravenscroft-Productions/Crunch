// (c)2025 Ravenscroft Productions

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "StormCore.generated.h"

class USphereComponent;

UCLASS()
class CRUNCH_API AStormCore : public ACharacter
{
	GENERATED_BODY()

public:
	AStormCore();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;
	
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	UPROPERTY(VisibleDefaultsOnly, Category = "Detection")
	USphereComponent* InfluenceRange;

	UFUNCTION()
	void NewInfluencerInRange(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void InfluencerLeftRange(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	void UpdateTeamWeight();
	
	int TeamOneInfluencerCount = 0;
	int TeamTwoInfluencerCount = 0;

	float TeamWeight = 0.0f;
};
