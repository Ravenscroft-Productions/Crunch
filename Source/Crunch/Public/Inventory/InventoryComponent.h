// (c)2025 Ravenscroft Productions

#pragma once

#include "CoreMinimal.h"
#include "InventoryItem.h"
#include "PDA_ShopItem.h"
#include "Components/ActorComponent.h"
#include "InventoryComponent.generated.h"


class UInventoryItem;
class UPDA_ShopItem;
class UAbilitySystemComponent;

DECLARE_MULTICAST_DELEGATE_OneParam(FOnItemAddedDelegate, const UInventoryItem* /*NewItem*/);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnItemRemovedDelegate, const FInventoryItemHandle& /*ItemHandle*/);
DECLARE_MULTICAST_DELEGATE_TwoParams(FOnItemStackCountChangeDelegate, const FInventoryItemHandle&, int /*NewCount*/);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class CRUNCH_API UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UInventoryComponent();
	FOnItemAddedDelegate OnItemAdded;
	FOnItemStackCountChangeDelegate OnItemStackCountChanged;
	FOnItemRemovedDelegate OnItemRemoved;
	void TryActivateItem(const FInventoryItemHandle& ItemHandle);
	void TryPurchase(const UPDA_ShopItem* ItemToPurchase);
	void SellItem(const FInventoryItemHandle& ItemHandle);
	float GetGold() const;
	FORCEINLINE int GetCapacity() const { return Capacity; }
	
	void ItemSlotChanged(const FInventoryItemHandle& Handle, int NewSlotNumber);
	UInventoryItem* GetInventoryItemByHandle(const FInventoryItemHandle& Handle) const;

	bool IsFullFor(const UPDA_ShopItem* Item) const;
	
	bool IsAllSlotOccupied() const;
	UInventoryItem* GetAvailableStackForItem(const UPDA_ShopItem* Item) const;
	bool FindIngredientForItem(const UPDA_ShopItem* Item, TArray<UInventoryItem*>& OutIngredients, const TArray<const UPDA_ShopItem*>& IngredientToIgnore = TArray<const UPDA_ShopItem*>());
	UInventoryItem* TryGetItemForShopItem(const UPDA_ShopItem* Item) const;

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditDefaultsOnly, Category = "Inventory")
	int Capacity = 6;
	
	UPROPERTY()
	UAbilitySystemComponent* OwnerAbilitySystemComponent;

	UPROPERTY()
	TMap<FInventoryItemHandle, UInventoryItem*> InventoryMap;
	
	/*************************************************************/
	/*                           Server                          */
	/*************************************************************/

	UFUNCTION(Server, Reliable, WithValidation)
	void Server_Purchase(const UPDA_ShopItem* ItemToPurchase);

	UFUNCTION(Server, Reliable, WithValidation)
	void Server_ActivateItem(FInventoryItemHandle ItemHandle);

	UFUNCTION(Server, Reliable, WithValidation)
	void Server_SellItem(FInventoryItemHandle ItemHandle);
	
	void GrantItem(const UPDA_ShopItem* NewItem);
	void ConsumeItem(UInventoryItem* Item);
	void RemoveItem(UInventoryItem* Item);
	bool TryItemCombination(const UPDA_ShopItem* NewItem);

	/*************************************************************/
	/*                           Client                          */
	/*************************************************************/

private:
	UFUNCTION(Client, Reliable)
	void Client_ItemAdded(FInventoryItemHandle AssignedHandle, const UPDA_ShopItem* Item);

	UFUNCTION(Client, Reliable)
	void Client_ItemRemoved(FInventoryItemHandle ItemHandle);

	UFUNCTION(Client, Reliable)
	void Client_ItemStackCountChanged(FInventoryItemHandle Handle, int NewCount);
};
