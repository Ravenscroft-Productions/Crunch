// (c)2025 Ravenscroft Productions

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "PDA_ShopItem.generated.h"

class UPDA_ShopItem;
class UGameplayAbility;
class UGameplayEffect;

USTRUCT(BlueprintType)
struct FItemCollection
{
	GENERATED_BODY()
public:
	FItemCollection();
	FItemCollection(const TArray<const UPDA_ShopItem*>& InItems);
	void AddItem(const UPDA_ShopItem* NewItem, bool bAddUnique = false);
	bool Contains(const UPDA_ShopItem* Item) const;
	const TArray<const UPDA_ShopItem*>& GetItems() const;
	
private:
	TArray<const UPDA_ShopItem*> Items;
};
/**
 * 
 */
UCLASS()
class CRUNCH_API UPDA_ShopItem : public UPrimaryDataAsset
{
	GENERATED_BODY()
public:
	virtual FPrimaryAssetId GetPrimaryAssetId() const override;
	static FPrimaryAssetType GetShopItemAssetType();
	UTexture2D* GetIcon() const;
	float GetPrice() const { return Price; }
	float GetSellPrice() const { return Price / 2.0f; }
	FText GetItemName() const { return ItemName; }
	FText GetItemDescription() const { return ItemDescription; }
	bool GetIsConsumable() const { return bIsConsumable; }
	TSubclassOf<UGameplayEffect> GetEquippedEffect() const { return EquippedEffect; }
	TSubclassOf<UGameplayEffect> GetConsumeEffect() const { return ConsumeEffect; }
	TSubclassOf<UGameplayAbility> GetGrantedAbility() const { return GrantedAbility; }
	bool GetIsStackable() const { return bIsStackable; }
	int GetMaxStackCount() const { return MaxStackCount; }
	const TArray<TSoftObjectPtr<UPDA_ShopItem>>& GetIngredients() const { return IngredientItems; };

private:
	UPROPERTY(EditDefaultsOnly, Category = "ShopItem")
	TSoftObjectPtr<UTexture2D> Icon;
	
	UPROPERTY(EditDefaultsOnly, Category = "ShopItem")
	float Price;
	
	UPROPERTY(EditDefaultsOnly, Category = "ShopItem")
	FText ItemName;
	
	UPROPERTY(EditDefaultsOnly, Category = "ShopItem")
	FText ItemDescription;
	
	UPROPERTY(EditDefaultsOnly, Category = "ShopItem")
	bool bIsConsumable;

	UPROPERTY(EditDefaultsOnly, Category = "ShopItem")
	TSubclassOf<UGameplayEffect> EquippedEffect;

	UPROPERTY(EditDefaultsOnly, Category = "ShopItem")
	TSubclassOf<UGameplayEffect> ConsumeEffect;

	UPROPERTY(EditDefaultsOnly, Category = "ShopItem")
	TSubclassOf<UGameplayAbility> GrantedAbility;

	UPROPERTY(EditDefaultsOnly, Category = "ShopItem")
	bool bIsStackable = false;

	UPROPERTY(EditDefaultsOnly, Category = "ShopItem")
	int MaxStackCount = 5;

	UPROPERTY(EditDefaultsOnly, Category = "ShopItem")
	TArray<TSoftObjectPtr<UPDA_ShopItem>> IngredientItems;
};
