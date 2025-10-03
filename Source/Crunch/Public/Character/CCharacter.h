// (c)2025 Ravenscroft Productions

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "GenericTeamAgentInterface.h"
#include "GAS/CGameplayAbilityTypes.h"
#include "CCharacter.generated.h"

class UAIPerceptionStimuliSourceComponent;
struct FGameplayTag;
class UWidgetComponent;
class UCAttributeSet;
class UCAbilitySystemComponent;

UCLASS()
class CRUNCH_API ACCharacter : public ACharacter, public IAbilitySystemInterface, public IGenericTeamAgentInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ACCharacter();
	void ServerSideInit();
	void ClientSideInit();
	bool IsLocallyControlledByPlayer() const;
	// Only called on Server
	virtual void PossessedBy(AController* NewController) override;

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	const TMap<ECAbilityInputID, TSubclassOf<UGameplayAbility>>& GetAbilities() const;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	/**********************************************************************/
	/*                            Gameplay Ability                        */
	/**********************************************************************/
public:
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	UFUNCTION(Server, Reliable, WithValidation)
	void Server_SendGameplayEventToSelf(const FGameplayTag& EventTag, const FGameplayEventData& EventData);
	
private:
	void BindGASChangeDelegates();
	void DeathTagUpdated(const FGameplayTag Tag, int32 NewCount);
	void StunTagUpdated(const FGameplayTag Tag, int32 NewCount);
	void AimTagUpdated(const FGameplayTag Tag, int32 NewCount);
	void MoveSpeedUpdated(const FOnAttributeChangeData& Data);
	void MaxHealthUpdated(const FOnAttributeChangeData& Data);
	void MaxManaUpdated(const FOnAttributeChangeData& Data);
	void SetIsAiming(bool bIsAiming);
	virtual void OnAimStateChanged(bool bIsAiming);
	
	UPROPERTY(VisibleDefaultsOnly, Category = "Gameplay Ability")
	UCAbilitySystemComponent* CAbilitySystemComponent;

	UPROPERTY()
	UCAttributeSet* CAttributeSet;
	
	/**********************************************************************/
	/*                                   UI                               */
	/**********************************************************************/
private:
	UPROPERTY(VisibleDefaultsOnly, Category = "UI")
	UWidgetComponent* OverheadWidgetComponent;

	void ConfigureOverheadStatusWidget();

	UPROPERTY(EditDefaultsOnly, Category = "UI")
	float OverheadStatsGaugeVisibilityCheckUpdateInterval = 1.0f;

	UPROPERTY(EditDefaultsOnly, Category = "UI")
	float OverheadStatsGaugeVisibilityRangeSquared = 10000000.0f;
	
	FTimerHandle OverheadStatsGaugeVisibilityUpdateTimerHandle;

	void UpdateOverheadStatsGaugeVisibility();
	void SetStatusGaugeEnabled(bool bIsEnabled);
	
	/**********************************************************************/
	/*                               Stun                                 */
	/**********************************************************************/
private:
	UPROPERTY(EditDefaultsOnly, Category = "Stun")
	UAnimMontage* StunMontage;

	virtual void OnStun();
	virtual void OnRecoverFromStun();
	
	/**********************************************************************/
	/*                         Death & Respawn                            */
	/**********************************************************************/
public:
	bool IsDead() const;
	void RespawnImmediately();
	
private:
	FTransform MeshRelativeTransform;
	
	UPROPERTY(EditDefaultsOnly, Category = "Death")
	UAnimMontage* DeathMontage;

	UPROPERTY(EditDefaultsOnly, Category = "Death")
	float DeathMontageFinishTimeShift = -0.8f;

	FTimerHandle DeathMontageTimerHandle;

	void DeathMontageFinished();
	void SetRagdollEnabled(bool bIsEnabled);
	
	void PlayDeathAnimation();
	void StartDeathSequence();
	void Respawn();

	virtual void OnDead();
	virtual void OnRespawn();

	/**********************************************************************/
	/*                                Team                                */
	/**********************************************************************/
public:
	/** Assigns Team Agent to given TeamID */
	virtual void SetGenericTeamId(const FGenericTeamId& NewTeamID) override;

	/** Retrieve team identifier in form of FGenericTeamID */
	virtual FGenericTeamId GetGenericTeamId() const override;
private:
	UPROPERTY(ReplicatedUsing = OnRep_TeamID)
	FGenericTeamId TeamID;

	UFUNCTION()
	virtual void OnRep_TeamID();
	
	/**********************************************************************/
	/*                                 AI                                 */
	/**********************************************************************/
private:
	void SetAIPerceptionStimuliSourceEnabled(bool bIsEnabled);
	
	UPROPERTY()
	UAIPerceptionStimuliSourceComponent* PerceptionStimuliSourceComponent;
};
