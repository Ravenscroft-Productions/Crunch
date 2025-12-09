// (c)2025 Ravenscroft Productions


#include "Widgets/PlayerTeamSlotWidget.h"

#include "Character/PA_CharacterDefinition.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"

void UPlayerTeamSlotWidget::NativeConstruct()
{
	Super::NativeConstruct();
	
	PlayerCharacterIcon->GetDynamicMaterial()->SetScalarParameterValue(CharacterEmptyMatParamName, 1.0f);
	CachedCharacterNameStr = "";
}

void UPlayerTeamSlotWidget::UpdateSlot(const FString& PlayerName, const UPA_CharacterDefinition* CharacterDefinition)
{
	CachedPlayerNameStr = PlayerName;
	
	if (CharacterDefinition)
	{
		PlayerCharacterIcon->GetDynamicMaterial()->SetTextureParameterValue(CharacterIconMatParamName, CharacterDefinition->LoadIcon());
		PlayerCharacterIcon->GetDynamicMaterial()->SetScalarParameterValue(CharacterEmptyMatParamName, 0.0f);
		CachedCharacterNameStr = CharacterDefinition->GetCharacterDisplayName();
	}
	else
	{
		PlayerCharacterIcon->GetDynamicMaterial()->SetScalarParameterValue(CharacterEmptyMatParamName, 1.0f);
		CachedCharacterNameStr = "";
	}
	
	UpdateNameText();
}

void UPlayerTeamSlotWidget::NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseEnter(InGeometry, InMouseEvent);
	NameText->SetText(FText::FromString(CachedCharacterNameStr));
	PlayAnimationForward(HoverAnim);
}

void UPlayerTeamSlotWidget::NativeOnMouseLeave(const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseLeave(InMouseEvent);
	NameText->SetText(FText::FromString(CachedPlayerNameStr));
	PlayAnimationReverse(HoverAnim);
}

void UPlayerTeamSlotWidget::UpdateNameText()
{
	if (IsHovered())
	{
		NameText->SetText(FText::FromString(CachedCharacterNameStr));
	}
	else
	{
		NameText->SetText(FText::FromString(CachedPlayerNameStr));
	}
}
