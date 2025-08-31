// (c)2025 Ravenscroft Productions


#include "Player/CPlayerCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"

ACPlayerCharacter::ACPlayerCharacter()
{
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>("Camera Boom");
	CameraBoom->SetupAttachment(GetRootComponent());

	ViewCam = CreateDefaultSubobject<UCameraComponent>("View Cam");
	ViewCam->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
}
