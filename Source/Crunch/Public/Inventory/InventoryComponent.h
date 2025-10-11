// (c)2025 Ravenscroft Productions

#pragma once

#include "CoreMinimal.h"
#include "InventoryItem.h"
#include "Components/ActorComponent.h"
#include "InventoryComponent.generated.h"


class UInventoryItem;
class UPDA_ShopItem;
class UAbilitySystemComponent;

DECLARE_MULTICAST_DELEGATE_OneParam(FOnItemAddedDelegate, const UInventoryItem* /*NewItem*/);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class CRUNCH_API UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UInventoryComponent();
	FOnItemAddedDelegate OnItemAdded;

	void TryPurchase(const UPDA_ShopItem* ItemToPurchase);
	float GetGold() const;
	FORCEINLINE int GetCapacity() const { return Capacity; }
	
	void ItemSlotChanged(const FInventoryItemHandle& Handle, int NewSlotNumber);
	UInventoryItem* GetInventoryItemByHandle(const FInventoryItemHandle& Handle) const;

	bool IsFullFor(const UPDA_ShopItem* Item) const;
	
	bool IsAllSlotOccupied() const;
	UInventoryItem* GetAvailableStackForItem(const UPDA_ShopItem* Item) const; 

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

	void GrantItem(const UPDA_ShopItem* NewItem);

	/*************************************************************/
	/*                           Client                          */
	/*************************************************************/

private:
	UFUNCTION(Client, Reliable)
	void Client_ItemAdded(FInventoryItemHandle AssignedHandle, const UPDA_ShopItem* Item);
};
