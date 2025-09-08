// (c)2025 Ravenscroft Productions

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "CCharacter.generated.h"

struct FGameplayTag;
class UWidgetComponent;
class UCAttributeSet;
class UCAbilitySystemComponent;

UCLASS()
class CRUNCH_API ACCharacter : public ACharacter, public IAbilitySystemInterface
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
private:
	void BindGASChangeDelegates();
	void DeathTagUpdated(const FGameplayTag Tag, int32 NewCount);
	
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
	
	/**********************************************************************/
	/*                         Death & Respawn                            */
	/**********************************************************************/
	void StartDeathSequence();
	void Respawn();
};
