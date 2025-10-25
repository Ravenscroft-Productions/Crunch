// (c)2025 Ravenscroft Productions

#pragma once

#include "CoreMinimal.h"
#include "RenderActorWidget.h"
#include "SkeletalMeshRenderWidget.generated.h"

class ASkeletalMeshRenderActor;
/**
 * 
 */
UCLASS()
class CRUNCH_API USkeletalMeshRenderWidget : public URenderActorWidget
{
	GENERATED_BODY()
public:
	virtual void NativeConstruct() override;
	
private:
	virtual void SpawnRenderActor() override;
	virtual ARenderActor* GetRenderActor() const override;
	
	UPROPERTY(EditDefaultsOnly, Category = "Skeletal Mesh Render")
	TSubclassOf<ASkeletalMeshRenderActor> SkeletalMeshRenderActorClass;

	UPROPERTY()
	ASkeletalMeshRenderActor* SkeletalMeshRenderActor;
};
