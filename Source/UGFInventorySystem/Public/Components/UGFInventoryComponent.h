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
    virtual bool HasItem_Implementation(const FUGFItem& Item) const override;
    virtual void SwapInventorySlot_Implementation(int32 SelectedIndex, int32 TargetIndex) override;
};
