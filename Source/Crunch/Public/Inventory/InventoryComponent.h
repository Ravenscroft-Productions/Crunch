// (c)2025 Ravenscroft Productions

#pragma once

#include "CoreMinimal.h"
#include "InventoryItem.h"
#include "Components/ActorComponent.h"
#include "InventoryComponent.generated.h"


class UInventoryItem;
class UPDA_ShopItem;
class UAbilitySystemComponent;

DECLARE_MULTICAST_DELEGATE_OneParam(FOnItemAddedDelegate, UInventoryItem* /*NewItem*/);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class CRUNCH_API UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UInventoryComponent();
	FOnItemAddedDelegate OnItemAdded;

	void TryPurchase(const UPDA_ShopItem* ItemToPurchase);
	float GetGold() const;

protected:
	virtual void BeginPlay() override;

private:
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
