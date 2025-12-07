// (c)2025 Ravenscroft Productions


#include "Widgets/LobbyWidget.h"

#include "Components/UniformGridPanel.h"
#include "Components/UniformGridSlot.h"
#include "Network/CNetStatics.h"
#include "Widgets/TeamSelectionWidget.h"

void ULobbyWidget::NativeConstruct()
{
	Super::NativeConstruct();
	ClearAndPopulateTeamSelectionSlots();
}

void ULobbyWidget::ClearAndPopulateTeamSelectionSlots()
{
	TeamSelectionSlotGridPanel->ClearChildren();
	
	for (int i = 0; i < UCNetStatics::GetPlayerCountPerTeam() * 2; ++i)
	{
		UTeamSelectionWidget* NewSelectionSlot = CreateWidget<UTeamSelectionWidget>(this, TeamSelectionWidgetClass);
		if (NewSelectionSlot)
		{
			NewSelectionSlot->SetSlotID(i);
			UUniformGridSlot* NewGridSlot = TeamSelectionSlotGridPanel->AddChildToUniformGrid(NewSelectionSlot);
			if (NewGridSlot)
			{
				int Row = i % UCNetStatics::GetPlayerCountPerTeam();
				int Column = i < UCNetStatics::GetPlayerCountPerTeam() ? 0 : 1;
				
				NewGridSlot->SetRow(Row);
				NewGridSlot->SetColumn(Column);
			}
			
			NewSelectionSlot->OnSlotClicked.AddUObject(this, &ULobbyWidget::SlotSelected);
			TeamSelectionSlots.Add(NewSelectionSlot);
		}
	}
}

void ULobbyWidget::SlotSelected(uint8 NewSlotID)
{
	UE_LOG(LogTemp, Warning, TEXT("Trying to switch to slot: %d"), NewSlotID);
}
