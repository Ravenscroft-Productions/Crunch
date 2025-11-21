// (c)2025 Ravenscroft Productions

#pragma once

#include "CoreMinimal.h"
#include "GenericTeamAgentInterface.h"
#include "Abilities/GameplayAbilityTargetActor.h"
#include "TA_Blackhole.generated.h"

class USphereComponent;

UCLASS()
class CRUNCH_API ATA_Blackhole : public AGameplayAbilityTargetActor, public IGenericTeamAgentInterface
{
	GENERATED_BODY()
public:
	ATA_Blackhole();
	void ConfigureBlackhole(float InBlackholeRange, float InPullSpeed, float InBlackholeDuration, const FGenericTeamId& InTeamId);
	
	virtual void SetGenericTeamId(const FGenericTeamId& InTeamId) override;
	virtual FGenericTeamId GetGenericTeamId() const override { return GetGenericTeamId(); }
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	
private:
	UPROPERTY(Replicated)
	FGenericTeamId TeamId;
	
	float PullSpeed;
	float BlackholeDuration;
	
	UPROPERTY(ReplicatedUsing = OnRep_BlackholeRange)
	float BlackholeRange;
	
	UFUNCTION()
	void OnRep_BlackholeRange();
	
	UPROPERTY(VisibleDefaultsOnly, Category = "Component")
	USceneComponent* RootComp;
	
	UPROPERTY(VisibleDefaultsOnly, Category = "Component")
	USphereComponent* DetectionSphereComponent;
	
	UPROPERTY(VisibleDefaultsOnly, Category = "Component")
	UParticleSystemComponent* VFXComponent;
	
	UFUNCTION()
	void ActorInBlackholeRange(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
	UFUNCTION()
	void ActorLeftBlackholeRange(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
};
