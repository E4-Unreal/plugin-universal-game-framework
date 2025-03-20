// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/UGFInventoryComponent.h"

#include "Logging.h"
#include "Data/UGFItemDefinition.h"

void UUGFInventoryComponent::AddItem_Implementation(const FUGFItem& Item, int32& Overflow)
{
    IUGFInventoryInterface::AddItem_Implementation(Item, Overflow);
}

void UUGFInventoryComponent::RemoveItem_Implementation(const FUGFItem& Item, int32& Underflow)
{
    // 초기화
    Underflow = Item.Amount;

    // null 검사
    if (Item.ItemDefinition == nullptr)
    {
        LOG(Error, TEXT("Item Definition is null"))
        return;
    }

    // 입력 유효성 검사
    if (Item.Amount <= 0)
    {
        LOG(Error, TEXT("Item Amount: %d"), Item.Amount);
        return;
    }

    // 아이템 보유 여부 확인
    if (!ItemInventoryIndicesMap.Contains(Item.ItemDefinition))
    {
        LOG(Log, TEXT("Inventory doesn't have item: %s"), *Item.ItemDefinition->GetDisplayName().ToString())
        return;
    }

    // Remove Item
    const auto& InventoryIndices = ItemInventoryIndicesMap[Item.ItemDefinition].Indices;
    TArray<int32> InventoryIndicesToRemove;
    InventoryIndicesToRemove.Reserve(InventoryIndices.Num());
    for (int32 InventoryIndex : InventoryIndices)
    {
        auto& InventorySlot = InventorySlots[InventoryIndex];
        if (InventorySlot.Amount > Underflow)
        {
            InventorySlot.Amount -= Underflow;
            Underflow = 0;
            break;
        }
        else if (InventorySlot.Amount == Underflow)
        {
            InventorySlot.Amount = 0;
            Underflow = 0;
            InventoryIndicesToRemove.Emplace(InventoryIndex);
            break;
        }
        else
        {
            InventorySlot.Amount = 0;
            Underflow -= InventorySlot.Amount;
            InventoryIndicesToRemove.Emplace(InventoryIndex);
        }
    }

    // Update InventorySlots
    for (int32 InventoryIndexToRemove : InventoryIndicesToRemove)
    {
        InventorySlots.Remove(InventoryIndexToRemove);
    }

    // Update ItemQuantityMap
    int32 InventoryItemQuantity = ItemQuantityMap[Item.ItemDefinition];
    int32 RemovedItemQuantity = Item.Amount - Underflow;
    if (InventoryItemQuantity <= RemovedItemQuantity)
    {
        ItemQuantityMap.Remove(Item.ItemDefinition);
    }
    else
    {
        ItemQuantityMap[Item.ItemDefinition] -= RemovedItemQuantity;
    }

    // Update ItemInventoryIndicesMap
    for (int32 InventoryIndexToRemove : InventoryIndicesToRemove)
    {
        ItemInventoryIndicesMap[Item.ItemDefinition].Indices.Remove(InventoryIndexToRemove);
    }

    LOG(Log, TEXT("Item removed from inventory.\nItem: %s\nInventoryItemQuantity: %d > %d"), %Item.ItemDefinition->GetDisplayName().ToString(), InventoryItemQuantity, InventoryItemQuantity - RemovedItemQuantity)
}

bool UUGFInventoryComponent::HasItem_Implementation(const FUGFItem& Item) const
{
    if (!ItemQuantityMap.Contains(Item.ItemDefinition)) return false;

    return ItemQuantityMap[Item.ItemDefinition] >= Item.Amount;
}

void UUGFInventoryComponent::SwapInventorySlot_Implementation(int32 SelectedIndex, int32 TargetIndex)
{
    IUGFInventoryInterface::SwapInventorySlot_Implementation(SelectedIndex, TargetIndex);
}
