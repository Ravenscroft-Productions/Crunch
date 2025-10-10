// (c)2025 Ravenscroft Productions

#pragma once

#include "CoreMinimal.h"
#include "ActiveGameplayEffectHandle.h"
#include "GameplayAbilitySpecHandle.h"
#include "UObject/Object.h"
#include "InventoryItem.generated.h"

class UAbilitySystemComponent;
class UPDA_ShopItem;

USTRUCT()
struct FInventoryItemHandle
{
	GENERATED_BODY()
public:
	FInventoryItemHandle();
	static FInventoryItemHandle InvalidHandle();
	static FInventoryItemHandle CreateHandle();

	bool IsValid() const;
	uint32 GetHandleId() const { return HandleId; }
	
private:
	explicit FInventoryItemHandle(uint32 Id);
	
	UPROPERTY()
	uint32 HandleId;

	static uint32 GenerateNextId();
	static uint32 GetInvalidId();
};

bool operator==(const FInventoryItemHandle& Lhs, const FInventoryItemHandle& Rhs);
uint32 GetTypeHash(const FInventoryItemHandle& Key);

/**
 * 
 */
UCLASS()
class CRUNCH_API UInventoryItem : public UObject
{
	GENERATED_BODY()
public:
	UInventoryItem();
	bool IsValid() const;
	void InitItem(const FInventoryItemHandle&  NewHandle, const UPDA_ShopItem* NewShopItem);
	const UPDA_ShopItem* GetShopItem() const { return ShopItem; }
	FInventoryItemHandle GetHandle() const { return Handle; }
	void ApplyGASModifications(UAbilitySystemComponent* AbilitySystemComponent);
	FORCEINLINE int GetStackCount() const { return StackCount; }
	void SetSlot(int NewSlot);
	
private:
	UPROPERTY()
	const UPDA_ShopItem* ShopItem;
	
	FInventoryItemHandle Handle;
	int StackCount;
	int Slot;

	FActiveGameplayEffectHandle AppliedEquippedEffectHandle;
	FGameplayAbilitySpecHandle GrantedAbilitySpecHandle;
};
