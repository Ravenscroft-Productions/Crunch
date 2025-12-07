// (c)2025 Ravenscroft Productions

#pragma once

#include "CoreMinimal.h"
#include "Engine/AssetManager.h"
#include "Inventory/PDA_ShopItem.h"
#include "CAssetManager.generated.h"

class UPA_CharacterDefinition;
/**
 * 
 */
UCLASS()
class CRUNCH_API UCAssetManager : public UAssetManager
{
	GENERATED_BODY()
public:
	static UCAssetManager& Get();
	void LoadCharacterDefinitions(const FStreamableDelegate& LoadFinishedCallback);
	bool GetLoadedCharacterDefinitions(TArray<UPA_CharacterDefinition*>& LoadedCharacterDefinitions) const;
	void LoadShopItems(const FStreamableDelegate& LoadFinishedCallback);
	bool GetLoadedShopItems(TArray<const UPDA_ShopItem*>& OutItems) const;
	const FItemCollection* GetCombinationForItem(const UPDA_ShopItem* Item) const;
	const FItemCollection* GetIngredientForItem(const UPDA_ShopItem* Item) const;

private:
	void ShopItemsLoadFinished(FStreamableDelegate Callback);
	void BuildItemMaps();
	void AddToCombinationMap(const UPDA_ShopItem* Ingredient, const UPDA_ShopItem* CombinationItem);

	UPROPERTY()
	TMap<const UPDA_ShopItem*, FItemCollection> CombinationMap;

	UPROPERTY()
	TMap<const UPDA_ShopItem*, FItemCollection> IngredientMap;
};
