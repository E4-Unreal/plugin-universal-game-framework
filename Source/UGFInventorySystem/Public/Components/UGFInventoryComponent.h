// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Interfaces/UGFInventoryInterface.h"
#include "Types/UGFInventorySlot.h"
#include "UGFInventoryComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FUGFInventoryUpdatedSignature, int32, SlotIndex);

USTRUCT(Atomic, BlueprintType)
struct FUGFInventoryIndices
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TSet<int32> Indices;

    bool IsEmpty() const { return Indices.IsEmpty(); }

    void AddIndex(int32 InIndex)
    {
        Indices.Emplace(InIndex);

        Sort();
    }

    void AddIndices(const TArray<int32>& InIndices)
    {
        for (int32 Index : InIndices)
        {
            Indices.Emplace(Index);
        }

        Sort();
    }

    void RemoveIndex(int32 InIndex)
    {
        Indices.Remove(InIndex);

        Sort();
    }

    void RemoveIndices(const TArray<int32>& InIndices)
    {
        for (int32 Index : InIndices)
        {
            Indices.Remove(Index);
        }

        Sort();
    }

    void Sort()
    {
        Indices.Sort([](const int32& Lhs, const int32& Rhs){ return Lhs < Rhs; });
    }
};


UCLASS(meta = (BlueprintSpawnableComponent))
class UGFINVENTORYSYSTEM_API UUGFInventoryComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    UPROPERTY(BlueprintAssignable)
    FUGFInventoryUpdatedSignature InventoryUpdated;

protected:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config", meta = (ClampMin = 0))
    int32 MaxSlotNum = 4;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
    TArray<FUGFItem> DefaultItems;

    // TMap<Index, Item>
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Transient, Category = "State")
    TMap<int32, FUGFInventorySlot> InventorySlots;

    // TMap<Item, Quantity>
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Transient, Category = "State")
    TMap<TObjectPtr<UUGFItemDefinition>, int32> CachedQuantityMap;

    // TMap<Item, InventoryIndices>
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Transient, Category = "State")
    TMap<TObjectPtr<UUGFItemDefinition>, FUGFInventoryIndices> CachedIndicesMap;

public:
    /* ActorComponent */

    virtual void BeginPlay() override;

    /* Getter */

    UFUNCTION(BlueprintPure, Category = "UI")
    FORCEINLINE int32 GetMaxSlotNum() const { return MaxSlotNum; }

    UFUNCTION(BlueprintPure, Category = "UI")
    const FUGFInventorySlot& GetInventorySlot(int32 Index) const { return InventorySlots.Contains(Index) ? InventorySlots[Index] : FUGFInventorySlot::EmptySlot; }

    /* UGFInventoryComponent */

    UFUNCTION(BlueprintCallable, Category = "Inventory")
    virtual void AddItem(const FUGFItem& Item, int32& Overflow);

    UFUNCTION(BlueprintCallable, Category = "Inventory")
    virtual void RemoveItem(const FUGFItem& Item, int32& Underflow);

    UFUNCTION(BlueprintCallable, Category = "Inventory")
    virtual bool HasItem(const FUGFItem& Item) const { return GetItemQuantity(Item.ItemDefinition) >= Item.Quantity; }

    UFUNCTION(BlueprintCallable, Category = "UI")
    virtual void SwapInventorySlot(int32 SourceIndex, int32 TargetIndex);

    UFUNCTION(BlueprintCallable, Category = "UI")
    virtual void ClearInventorySlot(int32 Index);

protected:
    UFUNCTION(BlueprintPure)
    static bool IsValidItem(const FUGFItem& Item);

    // 인벤토리에 보유 중인 특정 아이템의 개수
    UFUNCTION(BlueprintPure)
    FORCEINLINE int32 GetItemQuantity(UUGFItemDefinition* ItemDefinition) const { return CachedQuantityMap.Contains(ItemDefinition) ? CachedQuantityMap[ItemDefinition] : 0; }

    UFUNCTION(BlueprintCallable, Category = "AddItem")
    virtual void FillInventorySlots(UUGFItemDefinition* ItemDefinition, int32& Overflow);

    UFUNCTION(BlueprintCallable, Category = "AddItem")
    virtual void AddInventorySlots(UUGFItemDefinition* ItemDefinition, int32& Overflow);

    UFUNCTION(BlueprintCallable, Category = "RemoveItem")
    virtual void RemoveInventorySlots(UUGFItemDefinition* ItemDefinition, int32& Underflow);

    UFUNCTION(BlueprintCallable, Category = "CachedQuantityMap")
    virtual void AddCachedQuantityMap(UUGFItemDefinition* ItemDefinition, int32 QuantityToAdd);

    UFUNCTION(BlueprintCallable, Category = "CachedQuantityMap")
    virtual void RemoveCachedQuantityMap(UUGFItemDefinition* ItemDefinition, int32 QuantityToRemove);

    UFUNCTION(BlueprintCallable, Category = "CachedIndicesMap")
    virtual void AddCachedIndicesMap(UUGFItemDefinition* ItemDefinition, int32 Index);

    UFUNCTION(BlueprintCallable, Category = "CachedIndicesMap")
    virtual void RemoveCachedIndicesMap(UUGFItemDefinition* ItemDefinition, int32 Index);

    UFUNCTION(BlueprintCallable)
    virtual void SortInventorySlots() { InventorySlots.KeySort([](int32 Lhs, int32 Rhs){ return Lhs < Rhs; }); }

    UFUNCTION(BlueprintCallable)
    virtual void AddDefaultItems();

    UFUNCTION(BlueprintCallable)
    virtual void AddInventorySlot(int32 SlotIndex, UUGFItemDefinition* ItemDefinition, int32 ItemQuantity);

    UFUNCTION(BlueprintCallable)
    virtual void RemoveInventorySlot(int32 SlotIndex);

    UFUNCTION(BlueprintCallable)
    virtual void AddQuantityToSlot(int32 SlotIndex, int32 QuantityToAdd);

    UFUNCTION(BlueprintCallable)
    virtual void RemoveQuantityFromSlot(int32 SlotIndex, int32 QuantityToRemove);
};
