// (c)2025 Ravenscroft Productions


#include "Widgets/CharacterDisplay.h"

#include "Camera/CameraComponent.h"
#include "Character/PA_CharacterDefinition.h"


ACharacterDisplay::ACharacterDisplay()
{
	PrimaryActorTick.bCanEverTick = true;
	SetRootComponent(CreateDefaultSubobject<USceneComponent>("Root Comp"));
	
	MeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>("Mesh Component");
	MeshComponent->SetupAttachment(GetRootComponent());
	
	ViewCameraComponent = CreateDefaultSubobject<UCameraComponent>("View Camera Component");
	ViewCameraComponent->SetupAttachment(GetRootComponent());
}

void ACharacterDisplay::ConfigureWithCharacterDefinition(const UPA_CharacterDefinition* CharacterDefinition)
{
	if (!CharacterDefinition) return;
	
	MeshComponent->SetSkeletalMesh(CharacterDefinition->LoadDisplayMesh());
	MeshComponent->SetAnimationMode(EAnimationMode::AnimationBlueprint);
	MeshComponent->SetAnimInstanceClass(CharacterDefinition->LoadDisplayAnimationBP());
}
