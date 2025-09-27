// (c)2025 Ravenscroft Productions

#pragma once

#include "CoreMinimal.h"
#include "Character/CCharacter.h"
#include "InputActionValue.h"
#include "CPlayerCharacter.generated.h"

enum class ECAbilityInputID : uint8;
class UInputMappingContext;
class UInputAction;
class USpringArmComponent;
class UCameraComponent;
/**
 * 
 */
UCLASS()
class CRUNCH_API ACPlayerCharacter : public ACCharacter
{
	GENERATED_BODY()
public:
	ACPlayerCharacter();
	virtual void PawnClientRestart() override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
private:
	UPROPERTY(VisibleDefaultsOnly, Category = "View")
	USpringArmComponent* CameraBoom;

	UPROPERTY(VisibleDefaultsOnly, Category = "View")
	UCameraComponent* ViewCam;

	FVector GetLookRightDir() const;
	FVector GetMoveFwdDir() const;

	/********************************************************/
	/*                  Gameplay Abilities                  */
	/********************************************************/
private:
	virtual void OnAimStateChanged(bool bIsAiming) override;
	
	/********************************************************/
	/*                       Input                          */
	/********************************************************/
private:
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	UInputAction* JumpInputAction;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	UInputAction* LookInputAction;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	UInputAction* MoveInputAction;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TMap<ECAbilityInputID, UInputAction*> GameplayAbilityInputActions;
	
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	UInputMappingContext* GameplayInputMappingContext;

	void HandleLookInput(const FInputActionValue& InputActionValue);
	void HandleMoveInput(const FInputActionValue& InputActionValue);
	void HandleAbilityInput(const FInputActionValue& InputActionValue, ECAbilityInputID InputID);
	void SetInputEnabledFromPlayerController(bool bEnabled);
	
	/********************************************************/
	/*                        Stun                          */
	/********************************************************/
	virtual void OnStun() override;
	virtual void OnRecoverFromStun() override;
	
	/********************************************************/
	/*                   Death & Respawn                    */
	/********************************************************/
private:
	virtual void OnDead() override;
	virtual void OnRespawn() override;

	/********************************************************/
	/*                     Camera View                      */
	/********************************************************/
private:
	UPROPERTY(EditDefaultsOnly, Category = "View")
	FVector CameraAimLocalOffset;

	UPROPERTY(EditDefaultsOnly, Category = "View")
	float CameraLerpSpeed = 20.0f;

	FTimerHandle CameraLerpTimerHandle;

	void LerpCameraToLocalOffsetLocation(const FVector& Goal);
	void TickCameraLocalOffsetLerp(FVector Goal);
};