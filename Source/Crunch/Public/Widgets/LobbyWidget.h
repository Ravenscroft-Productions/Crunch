// (c)2025 Ravenscroft Productions

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "LobbyWidget.generated.h"

class UUniformGridPanel;
class UButton;
class UWidgetSwitcher;
/**
 * 
 */
UCLASS()
class CRUNCH_API ULobbyWidget : public UUserWidget
{
	GENERATED_BODY()
private:
	UPROPERTY(meta = (BindWidget))
	UWidgetSwitcher* MainSwitcher;
	
	UPROPERTY(meta = (BindWidget))
	UWidget* TeamSelectionRoot;
	
	UPROPERTY(meta = (BindWidget))
	UButton* StartHeroSelectionButton;
	
	UPROPERTY(meta = (BindWidget))
	UUniformGridPanel* TeamSelectionSlotGridPanel;
};
