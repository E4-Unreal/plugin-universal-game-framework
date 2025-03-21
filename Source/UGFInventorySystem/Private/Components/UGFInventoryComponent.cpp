// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/UGFInventoryComponent.h"

#include "Logging.h"
#include "Data/UGFItemDefinition.h"

void UUGFInventoryComponent::AddItem_Implementation(const FUGFItem& Item, int32& Overflow)
{
    // 초기화
    Overflow = Item.Amount;

    // Item 유효성 검사
    if (!IsValidItem(Item)) return;

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
    while (Overflow != 0 && InventorySlots.Num() < MaxInventorySlotNum)
    {
        if (!InventorySlots.Contains(NewInventorySlotIndex))
        {
            FUGFItem NewInventorySlotItem;
            NewInventorySlotItem.ItemDefinition = Item.ItemDefinition;

            if (MaxStack > Overflow)
            {
                NewInventorySlotItem.Amount = Overflow;
                Overflow = 0;
            }
            else if (MaxStack == Overflow)
            {
                NewInventorySlotItem.Amount = MaxStack;
                Overflow = 0;
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
    int32 QuantityToAdd = Item.Amount - Overflow;
    AddItemQuantity(Item.ItemDefinition, QuantityToAdd);

    // ItemInventoryIndicesMap 업데이트
    AddItemInventoryIndices(Item.ItemDefinition, InventoryIndicesToAdd);
}

void UUGFInventoryComponent::RemoveItem_Implementation(const FUGFItem& Item, int32& Underflow)
{
    // 초기화
    Underflow = Item.Amount;

    // Item 유효성 검사
    if (!IsValidItem(Item)) return;

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
            Underflow -= InventorySlot.Amount;
            InventorySlot.Amount = 0;
            InventoryIndicesToRemove.Emplace(InventoryIndex);
        }
    }

    for (int32 InventoryIndexToRemove : InventoryIndicesToRemove)
    {
        InventorySlots.Remove(InventoryIndexToRemove);
    }

    // ItemQuantityMap 업데이트
    int32 QuantityToRemove = Item.Amount - Underflow;
    RemoveItemQuantity(Item.ItemDefinition, QuantityToRemove);

    // ItemInventoryIndicesMap 업데이트
    RemoveItemInventoryIndices(Item.ItemDefinition, InventoryIndicesToRemove);
}

void UUGFInventoryComponent::SwapInventorySlot_Implementation(int32 SelectedIndex, int32 TargetIndex)
{
    IUGFInventoryInterface::SwapInventorySlot_Implementation(SelectedIndex, TargetIndex);
}

bool UUGFInventoryComponent::IsValidItem(const FUGFItem& Item) const
{
    // null 검사
    if (Item.ItemDefinition == nullptr)
    {
        LOG(Error, TEXT("Item Definition is null"))
        return false;
    }

    // 입력 유효성 검사
    if (Item.Amount <= 0)
    {
        LOG(Error, TEXT("Item Amount: %d"), Item.Amount);
        return false;
    }

    return true;
}

void UUGFInventoryComponent::AddItemQuantity(UUGFItemDefinition* ItemDefinition, int32 QuantityToAdd)
{
    int32 OldItemQuantity = GetItemQuantity(ItemDefinition);
    if (ItemQuantityMap.Contains(ItemDefinition))
    {
        ItemQuantityMap[ItemDefinition] += QuantityToAdd;
    }
    else
    {
        ItemQuantityMap.Emplace(ItemDefinition, QuantityToAdd);
    }
    int32 NewItemQuantity = GetItemQuantity(ItemDefinition);
    LOG(Log, TEXT("Item added to inventory.\nItem: %s\nItemQuantity: %d = %d + %d"), *ItemDefinition->GetDisplayName().ToString(), NewItemQuantity, OldItemQuantity, QuantityToAdd)
}

void UUGFInventoryComponent::AddItemInventoryIndices(UUGFItemDefinition* ItemDefinition,
    TArray<int32> InventoryIndicesToAdd)
{
    if (InventoryIndicesToAdd.IsEmpty()) return;

    if (!ItemInventoryIndicesMap.Contains(ItemDefinition)) ItemInventoryIndicesMap.Emplace(ItemDefinition, FUGFInventoryIndices());
    ItemInventoryIndicesMap[ItemDefinition].AddIndices(InventoryIndicesToAdd);
}

void UUGFInventoryComponent::RemoveItemQuantity(UUGFItemDefinition* ItemDefinition, int32 QuantityToRemove)
{
    int32 OldItemQuantity = GetItemQuantity(ItemDefinition);
    if (OldItemQuantity <= QuantityToRemove)
    {
        ItemQuantityMap.Remove(ItemDefinition);
    }
    else
    {
        ItemQuantityMap[ItemDefinition] -= QuantityToRemove;
    }
    int32 NewItemQuantity = GetItemQuantity(ItemDefinition);
    LOG(Log, TEXT("Item removed from inventory.\nItem: %s\nItemQuantity: %d = %d - %d"), *ItemDefinition->GetDisplayName().ToString(), NewItemQuantity, OldItemQuantity, QuantityToRemove)
}

void UUGFInventoryComponent::RemoveItemInventoryIndices(UUGFItemDefinition* ItemDefinition,
    TArray<int32> InventoryIndicesToRemove)
{
    if (InventoryIndicesToRemove.IsEmpty()) return;

    if (ItemInventoryIndicesMap.Contains(ItemDefinition))
    {
        ItemInventoryIndicesMap[ItemDefinition].RemoveIndices(InventoryIndicesToRemove);
        if (ItemInventoryIndicesMap[ItemDefinition].IsEmpty()) ItemInventoryIndicesMap.Remove(ItemDefinition);
    }
}
