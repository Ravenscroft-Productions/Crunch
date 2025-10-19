// (c)2025 Ravenscroft Productions

#pragma once

#include "CoreMinimal.h"
#include "ActiveGameplayEffectHandle.h"
#include "GameplayAbilitySpecHandle.h"
#include "GAS/CAttributeSet.h"
#include "UObject/Object.h"
#include "InventoryItem.generated.h"

class UGameplayAbility;
class UAbilitySystemComponent;
class UPDA_ShopItem;

DECLARE_MULTICAST_DELEGATE_OneParam(FOnAbilityCanCastUpdatedDelegate, bool /*bCanCast*/)

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
	FOnAbilityCanCastUpdatedDelegate OnAbilityCanCastUpdated;
	// Returns true if was able to add.
	bool AddStackCount();

	// Returns true if the stack is not empty after reducing.
	bool ReduceStackCount();

	// Returns true if was able to set.
	bool SetStackCount(int NewStackCount);
	
	bool IsStackFull() const;
	
	bool IsForItem(const UPDA_ShopItem* Item) const;
	bool IsGrantingAbility(TSubclassOf<UGameplayAbility> AbilityClass) const;
	bool IsGrantingAnyAbility() const;
	
	UInventoryItem();
	bool IsValid() const;
	void InitItem(const FInventoryItemHandle&  NewHandle, const UPDA_ShopItem* NewShopItem, UAbilitySystemComponent* AbilitySystemComponent);
	const UPDA_ShopItem* GetShopItem() const { return ShopItem; }
	FInventoryItemHandle GetHandle() const { return Handle; }

	bool TryActivateGrantedAbility();
	void ApplyConsumeEffect();
	void RemoveGASModifications();
	FORCEINLINE int GetStackCount() const { return StackCount; }
	void SetSlot(int NewSlot);

	float GetAbilityCooldownTimeRemaining() const;
	float GetAbilityCooldownDuration() const;
	float GetAbilityManaCost() const;
	bool CanCastAbility() const;
	FGameplayAbilitySpecHandle GetGrantedAbilitySpecHandle() const { return GrantedAbilitySpecHandle; }
	void SetGrantedAbilitySpecHandle(FGameplayAbilitySpecHandle SpecHandle) { GrantedAbilitySpecHandle = SpecHandle; }
	
private:
	void ApplyGASModifications();
	UAbilitySystemComponent* OwnerAbilitySystemComponent;
	void ManaUpdated(const FOnAttributeChangeData& ChangeData);
	
	UPROPERTY()
	const UPDA_ShopItem* ShopItem;
	
	FInventoryItemHandle Handle;
	int StackCount;
	int Slot;

	FActiveGameplayEffectHandle AppliedEquippedEffectHandle;
	FGameplayAbilitySpecHandle GrantedAbilitySpecHandle;
};
