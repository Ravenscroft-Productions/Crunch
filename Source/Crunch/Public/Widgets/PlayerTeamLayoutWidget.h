// (c)2025 Ravenscroft Productions

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Player/PlayerInfoTypes.h"
#include "PlayerTeamLayoutWidget.generated.h"

class UHorizontalBox;
class UPlayerTeamSlotWidget;
/**
 * 
 */
UCLASS()
class CRUNCH_API UPlayerTeamLayoutWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	virtual void NativeConstruct() override;
	void UpdatePlayerSelection(const TArray<FPlayerSelection>& PlayerSelections);
	
private:
	UPROPERTY(EditDefaultsOnly, Category = "Visual")
	float PlayerTeamWidgetSlotMargin = 5.0f;
	
	UPROPERTY(EditDefaultsOnly, Category = "Visual")
	TSubclassOf<UPlayerTeamSlotWidget> PlayerTeamSlotWidgetClass;
	
	UPROPERTY(meta=(BindWidget))
	UHorizontalBox* TeamOneLayoutBox;
	
	UPROPERTY(meta=(BindWidget))
	UHorizontalBox* TeamTwoLayoutBox;
	
	UPROPERTY()
	TArray<UPlayerTeamSlotWidget*> TeamSlotWidgets;
};
