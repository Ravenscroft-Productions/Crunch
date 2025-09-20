// (c)2025 Ravenscroft Productions

#pragma once

#include "CoreMinimal.h"
#include "GenericTeamAgentInterface.h"
#include "GameFramework/Actor.h"
#include "MinionBarrack.generated.h"

class AMinion;

UCLASS()
class CRUNCH_API AMinionBarrack : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AMinionBarrack();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(EditAnywhere, Category = "Spawn")
	FGenericTeamId BarrackTeamID;

	UPROPERTY(EditAnywhere, Category = "Spawn")
	int MinionPerGroup = 3;

	UPROPERTY(EditAnywhere, Category = "Spawn")
	float GroupSpawnInterval = 5.0f;
	
	UPROPERTY()
	TArray<AMinion*> MinionPool;

	UPROPERTY(EditAnywhere, Category = "Spawn")
	TSubclassOf<AMinion> MinionClass;

	UPROPERTY(EditAnywhere, Category = "Spawn")
	TArray<APlayerStart*> SpawnSpots;

	int NextSpawnSpotIndex = -1;

	const APlayerStart* GetNextSpawnSpot();

	void SpawnNewGroup();
	void SpawnNewMinions(int Amt);
	AMinion* GetNextAvailableMinion() const;

	FTimerHandle SpawnIntervalTimerHandle;	
};
