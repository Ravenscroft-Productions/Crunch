// (c)2025 Ravenscroft Productions

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MatchStatWidget.generated.h"

class AStormCore;
class UTextBlock;
class UImage;
/**
 * 
 */
UCLASS()
class CRUNCH_API UMatchStatWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	virtual void NativeConstruct() override;
	
private:
	UPROPERTY(EditDefaultsOnly, Category = "Match Stat")
	float ProgressUpdateInterval = 0.5f;

	UPROPERTY(EditDefaultsOnly, Category = "Match Stat")
	FName ProgressDynamicMaterialParamName = "Progress";
	
	UPROPERTY(meta = (BindWidget))
	UImage* ProgressImage;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* TeamOneCountText;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* TeamTwoCountText;

	UPROPERTY()
	AStormCore* StormCore;

	void UpdateTeamInfluence(int TeamOneCount, int TeamTwoCount);
	void MatchFinished(AActor* ViewTarget, int WinningTeam);
	void UpdateProgress();

	FTimerHandle UpdateProgressTimerHandle;
};
