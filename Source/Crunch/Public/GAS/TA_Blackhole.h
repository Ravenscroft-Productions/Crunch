// (c)2025 Ravenscroft Productions

#pragma once

#include "CoreMinimal.h"
#include "GenericTeamAgentInterface.h"
#include "Abilities/GameplayAbilityTargetActor.h"
#include "TA_Blackhole.generated.h"

class UNiagaraSystem;
class UNiagaraComponent;
class USphereComponent;

UCLASS()
class CRUNCH_API ATA_Blackhole : public AGameplayAbilityTargetActor, public IGenericTeamAgentInterface
{
	GENERATED_BODY()
public:
	ATA_Blackhole();
	void ConfigureBlackhole(float InBlackholeRange, float InPullSpeed, float InBlackholeDuration, const FGenericTeamId& InTeamId);
	
	virtual void SetGenericTeamId(const FGenericTeamId& InTeamId) override;
	virtual FGenericTeamId GetGenericTeamId() const override { return TeamId; }
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	virtual void StartTargeting(UGameplayAbility* Ability) override;
	virtual void Tick(float DeltaTime) override;
	
private:
	UPROPERTY(Replicated)
	FGenericTeamId TeamId;
	
	float PullSpeed;
	float BlackholeDuration;
	FTimerHandle BlackholeDurationTimerHandle;
	
	UPROPERTY(ReplicatedUsing = OnRep_BlackholeRange)
	float BlackholeRange;
	
	UPROPERTY(EditDefaultsOnly, Category = "VFX")
	FName BlackholeVFXOriginVariableName = "Origin";
	
	UPROPERTY(EditDefaultsOnly, Category = "VFX")
	UNiagaraSystem* BlackholeLinkVFX;
	
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
	
	void TryAddTarget(AActor* OtherTarget);
	void RemoveTarget(AActor* OtherTarget);
	
	TMap<AActor*, UNiagaraComponent*> ActorsInRangeMap;
	
	void StopBlackhole();
};
