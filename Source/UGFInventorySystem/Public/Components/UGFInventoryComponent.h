// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Interfaces/UGFInventoryInterface.h"
#include "UGFInventoryComponent.generated.h"

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
class UGFINVENTORYSYSTEM_API UUGFInventoryComponent : public UActorComponent, public IUGFInventoryInterface
{
    GENERATED_BODY()

protected:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config", meta = (ClampMin = 0))
    int32 MaxInventorySlotNum = 4;

    // TMap<Index, Item>
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Transient, Category = "State")
    TMap<int32, FUGFItem> InventorySlots;

    // TMap<Item, Quantity>
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Transient, Category = "State")
    TMap<TObjectPtr<UUGFItemDefinition>, int32> ItemQuantityMap;

    // TMap<Item, InventoryIndices>
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Transient, Category = "State")
    TMap<TObjectPtr<UUGFItemDefinition>, FUGFInventoryIndices> ItemInventoryIndicesMap;

public:
    /* IUGFInventoryInterface */

    virtual void AddItem_Implementation(const FUGFItem& Item, int32& Overflow) override;
    virtual void RemoveItem_Implementation(const FUGFItem& Item, int32& Underflow) override;
    virtual bool HasItem_Implementation(const FUGFItem& Item) const override { return GetItemQuantity(Item.ItemDefinition) >= Item.Amount; }
    virtual void SwapInventorySlot_Implementation(int32 SelectedIndex, int32 TargetIndex) override;

protected:
    UFUNCTION(BlueprintPure)
    bool IsValidItem(const FUGFItem& Item) const;

    // 인벤토리에 보유 중인 특정 아이템의 개수
    UFUNCTION(BlueprintPure)
    FORCEINLINE int32 GetItemQuantity(UUGFItemDefinition* ItemDefinition) const { return ItemQuantityMap.Contains(ItemDefinition) ? ItemQuantityMap[ItemDefinition] : 0; }

    UFUNCTION(BlueprintCallable, Category = "AddItem")
    virtual void FillInventorySlots(UUGFItemDefinition* ItemDefinition, int32& Overflow);

    UFUNCTION(BlueprintCallable, Category = "AddItem")
    virtual TArray<int32> AddInventorySlots(UUGFItemDefinition* ItemDefinition, int32& Overflow);

    UFUNCTION(BlueprintCallable, Category = "AddItem")
    virtual void AddItemQuantity(UUGFItemDefinition* ItemDefinition, int32 QuantityToAdd);

    UFUNCTION(BlueprintCallable, Category = "AddItem")
    virtual void AddItemInventoryIndices(UUGFItemDefinition* ItemDefinition, TArray<int32> InventoryIndicesToAdd);

    UFUNCTION(BlueprintCallable, Category = "RemoveItem")
    virtual TArray<int32> RemoveInventorySlots(UUGFItemDefinition* ItemDefinition, int32& Underflow);

    UFUNCTION(BlueprintCallable, Category = "RemoveItem")
    virtual void RemoveItemQuantity(UUGFItemDefinition* ItemDefinition, int32 QuantityToRemove);

    UFUNCTION(BlueprintCallable, Category = "RemoveItem")
    virtual void RemoveItemInventoryIndices(UUGFItemDefinition* ItemDefinition, TArray<int32> InventoryIndicesToRemove);

    UFUNCTION(BlueprintCallable, Category = "AddItem")
    virtual void AddInventoryIndex(UUGFItemDefinition* ItemDefinition, int32 Index);

    UFUNCTION(BlueprintCallable, Category = "RemoveItem")
    virtual void RemoveInventoryIndex(UUGFItemDefinition* ItemDefinition, int32 Index);
};
