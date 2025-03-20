// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/UGFInventoryComponent.h"

#include "Logging.h"
#include "UGFItemSystemFunctionLibrary.h"
#include "Data/UGFItemDefinition.h"

void UUGFInventoryComponent::AddItem_Implementation(const FUGFItem& Item, int32& Overflow)
{
    // 초기화
    Overflow = Item.Amount;

    // Item 유효성 검사
    if (!UUGFItemSystemFunctionLibrary::IsValidItem(Item)) return;

    // 변수 선언 및 초기화
    int32 MaxStack = Item.ItemDefinition->GetMaxStack();

    // 기존 인벤토리 슬롯 채워넣기
    if (ItemInventoryIndicesMap.Contains(Item.ItemDefinition))
    {
        const auto& InventoryIndices = ItemInventoryIndicesMap[Item.ItemDefinition].Indices;
        for (int32 InventoryIndex : InventoryIndices)
        {
            auto& InventorySlot = InventorySlots[InventoryIndex];
            if (InventorySlot.IsFull()) continue;

            int32 Capacity = MaxStack - InventorySlot.Amount;
            if (Capacity > Overflow)
            {
                InventorySlot.Amount += Overflow;
                Overflow = 0;
                break;
            }
            else if (Capacity == Overflow)
            {
                InventorySlot.Amount = MaxStack;
                Overflow = 0;
                break;
            }
            else
            {
                InventorySlot.Amount = MaxStack;
                Overflow -= Capacity;
            }
        }
    }

    // 새로운 인벤토리 슬롯 생성
    int32 NewInventorySlotIndex = 0;
    TArray<int32> InventoryIndicesToAdd;
    while (Overflow == 0 || InventorySlots.Num() >= MaxInventorySlotNum)
    {
        if (!InventorySlots.Contains(NewInventorySlotIndex))
        {
            FUGFItem NewInventorySlotItem;
            NewInventorySlotItem.ItemDefinition = Item.ItemDefinition;

            if (MaxStack > Overflow)
            {
                NewInventorySlotItem.Amount = Overflow;
                Overflow = 0;
                break;
            }
            else if (MaxStack == Overflow)
            {
                NewInventorySlotItem.Amount = MaxStack;
                Overflow = 0;
                break;
            }
            else
            {
                NewInventorySlotItem.Amount = MaxStack;
                Overflow -= MaxStack;
            }

            InventorySlots.Emplace(NewInventorySlotIndex, NewInventorySlotItem);
            InventoryIndicesToAdd.Emplace(NewInventorySlotIndex);
        }
        ++NewInventorySlotIndex;
    }

    InventorySlots.KeySort([](int32 Lhs, int32 Rhs){ return Lhs < Rhs; });

    // ItemQuantityMap 업데이트
    int32 InventoryItemQuantity = ItemQuantityMap.Contains(Item.ItemDefinition) ? ItemQuantityMap[Item.ItemDefinition] : 0;
    int32 AddedItemQuantity = Item.Amount - Overflow;
    if (ItemQuantityMap.Contains(Item.ItemDefinition))
    {
        ItemQuantityMap[Item.ItemDefinition] += AddedItemQuantity;
    }
    else
    {
        ItemQuantityMap.Emplace(Item.ItemDefinition, AddedItemQuantity);
    }

    // ItemInventoryIndicesMap 업데이트
    ItemInventoryIndicesMap[Item.ItemDefinition].AddIndices(InventoryIndicesToAdd);

    LOG(Log, TEXT("Item removed from inventory.\nItem: %s\nInventoryItemQuantity: %d > %d"), %Item.ItemDefinition->GetDisplayName().ToString(), InventoryItemQuantity, InventoryItemQuantity + AddedItemQuantity)
}

void UUGFInventoryComponent::RemoveItem_Implementation(const FUGFItem& Item, int32& Underflow)
{
    // 초기화
    Underflow = Item.Amount;

    // Item 유효성 검사
    if (!UUGFItemSystemFunctionLibrary::IsValidItem(Item)) return;

    // 아이템 보유 여부 확인
    if (!ItemInventoryIndicesMap.Contains(Item.ItemDefinition))
    {
        LOG(Log, TEXT("Inventory doesn't have item: %s"), *Item.ItemDefinition->GetDisplayName().ToString())
        return;
    }

    // Update InventorySlots
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

    for (int32 InventoryIndexToRemove : InventoryIndicesToRemove)
    {
        InventorySlots.Remove(InventoryIndexToRemove);
    }

    // ItemQuantityMap 업데이트
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

    // ItemInventoryIndicesMap 업데이트
    ItemInventoryIndicesMap[Item.ItemDefinition].RemoveIndices(InventoryIndicesToRemove);

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
