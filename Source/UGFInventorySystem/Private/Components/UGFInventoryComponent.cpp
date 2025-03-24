// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/UGFInventoryComponent.h"

#include "Logging.h"
#include "Data/UGFInventoryItemConfig.h"
#include "Data/UGFItemDefinition.h"

void UUGFInventoryComponent::AddItem_Implementation(const FUGFItem& Item, int32& Overflow)
{
    check(Item.ItemDefinition != nullptr)

    // 초기화
    Overflow = Item.Quantity;

    // Item 유효성 검사
    if (!IsValidItem(Item)) return;

    // 기존 인벤토리 슬롯 채워넣기
    FillInventorySlots(Item.ItemDefinition, Overflow);

    // 새로운 인벤토리 슬롯 생성
    AddInventorySlots(Item.ItemDefinition, Overflow);

    // ItemQuantityMap 업데이트
    int32 QuantityToAdd = Item.Quantity - Overflow;
    if (QuantityToAdd > 0)
    {
        AddItemQuantity(Item.ItemDefinition, QuantityToAdd);
        SortInventorySlots();
    }

    LOG(Log, TEXT("Try add item(%s) > Quantity: %d, Overflow: %d"), *Item.ItemDefinition->GetDisplayName().ToString(), Item.Quantity, Overflow)
}

void UUGFInventoryComponent::RemoveItem_Implementation(const FUGFItem& Item, int32& Underflow)
{
    check(Item.ItemDefinition != nullptr)

    // 초기화
    Underflow = Item.Quantity;

    // Item 유효성 검사
    if (!IsValidItem(Item)) return;

    // 기존 인벤토리 슬롯 비우기
    RemoveInventorySlots(Item.ItemDefinition, Underflow);

    // ItemQuantityMap 업데이트
    int32 QuantityToRemove = Item.Quantity - Underflow;
    if (QuantityToRemove > 0)
    {
        RemoveItemQuantity(Item.ItemDefinition, QuantityToRemove);
        SortInventorySlots();
    }

    LOG(Log, TEXT("Try remove item(%s) > Quantity: %d, Underflow: %d"), *Item.ItemDefinition->GetDisplayName().ToString(), Item.Quantity, Underflow)
}

void UUGFInventoryComponent::SwapInventorySlot_Implementation(int32 SelectedIndex, int32 TargetIndex)
{
    IUGFInventoryInterface::SwapInventorySlot_Implementation(SelectedIndex, TargetIndex);
}

bool UUGFInventoryComponent::IsValidItem(const FUGFItem& Item)
{
    if (!Item.IsValid()) return false;

    // InventoryItemConfig 설정 여부 확인
    const UUGFInventoryItemConfig* InventoryItemConfig = UUGFInventoryItemConfig::GetFromItemDefinition(Item.ItemDefinition);
    if (InventoryItemConfig == nullptr)
    {
        LOG_NULL(InventoryItemConfig);
        return false;
    }

    return true;
}

void UUGFInventoryComponent::FillInventorySlots(UUGFItemDefinition* ItemDefinition, int32& Overflow)
{
    check(ItemDefinition != nullptr);

    if (!ItemInventoryIndicesMap.Contains(ItemDefinition)) return;

    const auto& InventoryItemConfig = UUGFInventoryItemConfig::GetFromItemDefinition(ItemDefinition);
    if (InventoryItemConfig == nullptr) return;

    const auto& Data = InventoryItemConfig->GetData();

    int32 MaxStack = Data.MaxStack;
    const auto& InventoryIndices = ItemInventoryIndicesMap[ItemDefinition].Indices;
    for (int32 InventoryIndex : InventoryIndices)
    {
        auto& InventorySlot = InventorySlots[InventoryIndex];
        if (InventorySlot.Quantity >= MaxStack) continue;

        int32 Capacity = MaxStack - InventorySlot.Quantity;
        if (Capacity > Overflow)
        {
            SetInventoryIndex(InventoryIndex, ItemDefinition, InventorySlot.Quantity + Overflow);
            Overflow = 0;
        }
        else if (Capacity == Overflow)
        {
            SetInventoryIndex(InventoryIndex, ItemDefinition, MaxStack);
            Overflow = 0;
        }
        else
        {
            SetInventoryIndex(InventoryIndex, ItemDefinition, MaxStack);
            Overflow -= Capacity;
        }

        if (Overflow <= 0) break;
    }
}

void UUGFInventoryComponent::AddInventorySlots(UUGFItemDefinition* ItemDefinition, int32& Overflow)
{
    check(ItemDefinition != nullptr);

    const auto& InventoryItemConfig = UUGFInventoryItemConfig::GetFromItemDefinition(ItemDefinition);
    if (InventoryItemConfig == nullptr) return;

    const auto& Data = InventoryItemConfig->GetData();

    int32 MaxStack = Data.MaxStack;
    int32 NewInventorySlotIndex = 0;
    while (Overflow != 0 && InventorySlots.Num() < MaxInventorySlotNum)
    {
        if (!InventorySlots.Contains(NewInventorySlotIndex))
        {
            if (MaxStack > Overflow)
            {
                SetInventoryIndex(NewInventorySlotIndex, ItemDefinition, Overflow);
                Overflow = 0;
            }
            else if (MaxStack == Overflow)
            {
                SetInventoryIndex(NewInventorySlotIndex, ItemDefinition, MaxStack);
                Overflow = 0;
            }
            else
            {
                SetInventoryIndex(NewInventorySlotIndex, ItemDefinition, MaxStack);
                Overflow -= MaxStack;
            }
        }
        ++NewInventorySlotIndex;
    }
}

void UUGFInventoryComponent::RemoveInventorySlots(UUGFItemDefinition* ItemDefinition, int32& Underflow)
{
    check(ItemDefinition != nullptr);

    if (!ItemInventoryIndicesMap.Contains(ItemDefinition)) return;

    TArray<int32> InventoryIndices = ItemInventoryIndicesMap[ItemDefinition].Indices.Array();
    for (int32 InventoryIndex : InventoryIndices)
    {
        auto& InventorySlot = InventorySlots[InventoryIndex];
        if (InventorySlot.Quantity > Underflow)
        {
            SetInventoryIndex(InventoryIndex, ItemDefinition, InventorySlot.Quantity - Underflow);
            Underflow = 0;
        }
        else if (InventorySlot.Quantity == Underflow)
        {
            SetInventoryIndex(InventoryIndex, ItemDefinition, 0);
            Underflow = 0;
        }
        else
        {
            Underflow -= InventorySlot.Quantity;
            SetInventoryIndex(InventoryIndex, ItemDefinition, 0);
        }

        if (Underflow == 0) break;
    }
}

void UUGFInventoryComponent::AddItemQuantity(UUGFItemDefinition* ItemDefinition, int32 QuantityToAdd)
{
    check(ItemDefinition != nullptr);

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
    LOG(Log, TEXT("Item added to inventory: %s > %d = %d + %d"), *ItemDefinition->GetDisplayName().ToString(), NewItemQuantity, OldItemQuantity, QuantityToAdd)
}

void UUGFInventoryComponent::RemoveItemQuantity(UUGFItemDefinition* ItemDefinition, int32 QuantityToRemove)
{
    check(ItemDefinition != nullptr);

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
    LOG(Log, TEXT("Item removed from inventory: %s > %d = %d - %d"), *ItemDefinition->GetDisplayName().ToString(), NewItemQuantity, OldItemQuantity, QuantityToRemove)
}

void UUGFInventoryComponent::AddInventoryIndex(UUGFItemDefinition* ItemDefinition, int32 Index)
{
    if (!ItemInventoryIndicesMap.Contains(ItemDefinition)) ItemInventoryIndicesMap.Emplace(ItemDefinition, FUGFInventoryIndices());

    ItemInventoryIndicesMap[ItemDefinition].AddIndex(Index);
    LOG(Log, TEXT("InventoryIndex added: %s > %d"), *ItemDefinition->GetDisplayName().ToString(), Index)
}

void UUGFInventoryComponent::RemoveInventoryIndex(UUGFItemDefinition* ItemDefinition, int32 Index)
{
    if (ItemInventoryIndicesMap.Contains(ItemDefinition))
    {
        ItemInventoryIndicesMap[ItemDefinition].RemoveIndex(Index);
        LOG(Log, TEXT("InventoryIndex removed: %s > %d"), *ItemDefinition->GetDisplayName().ToString(), Index)

        if (ItemInventoryIndicesMap[ItemDefinition].IsEmpty()) ItemInventoryIndicesMap.Remove(ItemDefinition);
    }
}

void UUGFInventoryComponent::SetInventoryIndex(int32 Index, UUGFItemDefinition* ItemDefinition, int32 ItemQuantity)
{
    check(ItemQuantity >= 0)

    int32 OldItemQuantity = 0;
    int32 NewItemQuantity = ItemQuantity;
    if (InventorySlots.Contains(Index))
    {
        check(InventorySlots[Index].ItemDefinition == ItemDefinition)

        // 기존 아이템 수량 저장
        OldItemQuantity = InventorySlots[Index].Quantity;

        // 아이템 수량 변경 혹은 인벤토리 슬롯 비우기
        if (NewItemQuantity <= 0)
        {
            RemoveInventoryIndex(ItemDefinition, Index);
            InventorySlots.Remove(Index);
        }
        else
        {
            InventorySlots[Index].Quantity = NewItemQuantity;
        }
    }
    else if (ItemQuantity > 0)
    {
        // 빈 인벤토리 슬롯에 아이템 추가
        FUGFItem NewItem
        {
            ItemDefinition,
            NewItemQuantity
        };
        InventorySlots.Emplace(Index, NewItem);
        AddInventoryIndex(ItemDefinition, Index);
    }

    LOG(Log, TEXT("InventorySlots[%d](%s): %d > %d"), Index, *ItemDefinition->GetDisplayName().ToString(), OldItemQuantity, NewItemQuantity)
}
