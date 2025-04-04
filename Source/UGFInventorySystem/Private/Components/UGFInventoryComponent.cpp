// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/UGFInventoryComponent.h"

#include "Logging.h"
#include "Data/UGFInventoryItemConfig.h"
#include "Data/UGFItemDefinition.h"
#include "Types/UGFInventorySlot.h"

void UUGFInventoryComponent::BeginPlay()
{
    Super::BeginPlay();

    AddDefaultItems();
}

void UUGFInventoryComponent::AddItem(const FUGFItem& Item, int32& Overflow)
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

    LOG(Log, TEXT("Try add item(%s) > Quantity: %d, Overflow: %d"), *Item.ItemDefinition->GetDisplayName().ToString(), Item.Quantity, Overflow)
}

void UUGFInventoryComponent::RemoveItem(const FUGFItem& Item, int32& Underflow)
{
    check(Item.ItemDefinition != nullptr)

    // 초기화
    Underflow = Item.Quantity;

    // Item 유효성 검사
    if (!IsValidItem(Item)) return;

    // 기존 인벤토리 슬롯 비우기
    RemoveInventorySlots(Item.ItemDefinition, Underflow);

    LOG(Log, TEXT("Try remove item(%s) > Quantity: %d, Underflow: %d"), *Item.ItemDefinition->GetDisplayName().ToString(), Item.Quantity, Underflow)
}

void UUGFInventoryComponent::SwapInventorySlot(int32 SourceIndex, int32 TargetIndex)
{
    // 유효성 검사
    if (SourceIndex < 0 || TargetIndex < 0 || SourceIndex == TargetIndex) return;

    const auto& SourceInventorySlot = GetInventorySlot(SourceIndex);
    const auto& TargetInventorySlot = GetInventorySlot(TargetIndex);

    if (SourceInventorySlot.IsEmpty()) return;
    if (TargetInventorySlot.IsEmpty())
    {
        RemoveInventorySlot(SourceIndex);
        AddInventorySlot(TargetIndex, SourceInventorySlot.ItemDefinition, SourceInventorySlot.Quantity);
        return;
    }

    if (SourceInventorySlot.ItemDefinition != TargetInventorySlot.ItemDefinition || TargetInventorySlot.IsFull())
    {
        RemoveInventorySlot(SourceIndex);
        RemoveInventorySlot(TargetIndex);

        AddInventorySlot(SourceIndex, TargetInventorySlot.ItemDefinition, TargetInventorySlot.Quantity);
        AddInventorySlot(TargetIndex, SourceInventorySlot.ItemDefinition, SourceInventorySlot.Quantity);
    }
    else
    {
        int32 Capacity = TargetInventorySlot.GetCapacity();
        int32 QuantityToMove = Capacity >= SourceInventorySlot.Quantity ? SourceInventorySlot.Quantity : Capacity;
        AddQuantityToSlot(TargetIndex, QuantityToMove);
        RemoveQuantityFromSlot(SourceIndex, QuantityToMove);
    }
}

void UUGFInventoryComponent::ClearInventorySlot(int32 Index)
{
    RemoveInventorySlot(Index);
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
    // 기존 인벤토리 슬롯 확인
    if (!CachedIndicesMap.Contains(ItemDefinition)) return;

    // 인벤토리 전용 아이템 데이터 가져오기
    auto InventoryItemConfig = UUGFInventoryItemConfig::GetFromItemDefinition(ItemDefinition);
    const auto& Data = InventoryItemConfig->GetData();
    int32 MaxStack = Data.MaxStack;

    // 기존 인벤토리 슬롯 채우기
    const auto& InventoryIndices = CachedIndicesMap[ItemDefinition].Indices;
    for (int32 InventoryIndex : InventoryIndices)
    {
        // 기존 인벤토리 슬롯 용량 확인
        auto& InventorySlot = InventorySlots[InventoryIndex];
        int32 Capacity = MaxStack - InventorySlot.Quantity;
        if (Capacity <= 0) continue;

        // 기존 인벤토리 슬롯에 추가할 수량 계산
        int32 QuantityToAdd = Capacity > Overflow ? Overflow : Capacity;
        Overflow -= QuantityToAdd;

        // 기존 인벤토리 슬롯 채우기
        AddQuantityToSlot(InventoryIndex, QuantityToAdd);

        if (Overflow <= 0) break;
    }
}

void UUGFInventoryComponent::AddInventorySlots(UUGFItemDefinition* ItemDefinition, int32& Overflow)
{
    // 인벤토리 전용 아이템 데이터 가져오기
    auto InventoryItemConfig = UUGFInventoryItemConfig::GetFromItemDefinition(ItemDefinition);
    const auto& Data = InventoryItemConfig->GetData();
    int32 MaxStack = Data.MaxStack;

    // 빈 인벤토리 슬롯에 아이템 추가
    for (int32 Index = 0; Index < MaxSlotNum; ++Index)
    {
        // 빈 인벤토리 슬롯인지 확인
        if (InventorySlots.Contains(Index)) continue;

        // 새로운 인벤토리 슬롯에 추가할 수량 계산
        int32 QuantityToAdd = MaxStack > Overflow ? Overflow : MaxStack;
        Overflow -= QuantityToAdd;

        // 새로운 인벤토리 슬롯 생성 및 추가
        AddInventorySlot(Index, ItemDefinition, QuantityToAdd);

        if (Overflow <= 0) break;
    }

    // 인벤토리 슬롯 정렬
    SortInventorySlots();
}

void UUGFInventoryComponent::RemoveInventorySlots(UUGFItemDefinition* ItemDefinition, int32& Underflow)
{
    check(ItemDefinition != nullptr);

    if (!CachedIndicesMap.Contains(ItemDefinition)) return;

    TArray<int32> InventoryIndices = CachedIndicesMap[ItemDefinition].Indices.Array();
    for (int32 InventoryIndex : InventoryIndices)
    {
        // 기존 인벤토리 슬롯에서 제거할 수량 계산
        auto& InventorySlot = InventorySlots[InventoryIndex];
        int32 QuantityToRemove = InventorySlot.Quantity > Underflow ? Underflow : InventorySlot.Quantity;
        Underflow -= QuantityToRemove;

        // 기존 인벤토리 슬롯에서 수량 제거
        RemoveQuantityFromSlot(InventoryIndex, QuantityToRemove);

        if (Underflow == 0) break;
    }

    // 인벤토리 슬롯 정렬
    SortInventorySlots();
}

void UUGFInventoryComponent::AddCachedQuantityMap(UUGFItemDefinition* ItemDefinition, int32 QuantityToAdd)
{
    check(ItemDefinition != nullptr);

    int32 OldItemQuantity = GetItemQuantity(ItemDefinition);
    if (CachedQuantityMap.Contains(ItemDefinition))
    {
        CachedQuantityMap[ItemDefinition] += QuantityToAdd;
    }
    else
    {
        CachedQuantityMap.Emplace(ItemDefinition, QuantityToAdd);
    }
    int32 NewItemQuantity = GetItemQuantity(ItemDefinition);
    LOG(Log, TEXT("Item added to inventory: %s > %d = %d + %d"), *ItemDefinition->GetDisplayName().ToString(), NewItemQuantity, OldItemQuantity, QuantityToAdd)
}

void UUGFInventoryComponent::RemoveCachedQuantityMap(UUGFItemDefinition* ItemDefinition, int32 QuantityToRemove)
{
    check(ItemDefinition != nullptr);

    int32 OldItemQuantity = GetItemQuantity(ItemDefinition);
    if (OldItemQuantity <= QuantityToRemove)
    {
        CachedQuantityMap.Remove(ItemDefinition);
    }
    else
    {
        CachedQuantityMap[ItemDefinition] -= QuantityToRemove;
    }
    int32 NewItemQuantity = GetItemQuantity(ItemDefinition);
    LOG(Log, TEXT("Item removed from inventory: %s > %d = %d - %d"), *ItemDefinition->GetDisplayName().ToString(), NewItemQuantity, OldItemQuantity, QuantityToRemove)
}

void UUGFInventoryComponent::AddCachedIndicesMap(UUGFItemDefinition* ItemDefinition, int32 Index)
{
    if (!CachedIndicesMap.Contains(ItemDefinition)) CachedIndicesMap.Emplace(ItemDefinition, FUGFInventoryIndices());

    CachedIndicesMap[ItemDefinition].AddIndex(Index);
    LOG(Log, TEXT("InventoryIndex added: %s > %d"), *ItemDefinition->GetDisplayName().ToString(), Index)
}

void UUGFInventoryComponent::RemoveCachedIndicesMap(UUGFItemDefinition* ItemDefinition, int32 Index)
{
    if (CachedIndicesMap.Contains(ItemDefinition))
    {
        CachedIndicesMap[ItemDefinition].RemoveIndex(Index);
        LOG(Log, TEXT("InventoryIndex removed: %s > %d"), *ItemDefinition->GetDisplayName().ToString(), Index)

        if (CachedIndicesMap[ItemDefinition].IsEmpty()) CachedIndicesMap.Remove(ItemDefinition);
    }
}

void UUGFInventoryComponent::AddDefaultItems()
{
    for (const auto& DefaultItem : DefaultItems)
    {
        int32 Overflow;
        AddItem(DefaultItem, Overflow);
    }
}

void UUGFInventoryComponent::AddInventorySlot(int32 SlotIndex, UUGFItemDefinition* ItemDefinition, int32 ItemQuantity)
{
    // 유효성 검사
    if (SlotIndex < 0 || ItemDefinition == nullptr || ItemQuantity <= 0) return;

    // 이미 존재하는 경우
    if (InventorySlots.Contains(SlotIndex)) return;

    // 새로운 슬롯 생성
    FUGFInventorySlot NewInventorySlot;
    NewInventorySlot.Index = SlotIndex;
    NewInventorySlot.ItemDefinition = ItemDefinition;
    NewInventorySlot.Quantity = ItemQuantity;

    // 슬롯 추가
    InventorySlots.Emplace(SlotIndex, NewInventorySlot);

    // 캐시 업데이트
    AddCachedIndicesMap(ItemDefinition, SlotIndex);
    AddCachedQuantityMap(ItemDefinition, ItemQuantity);

    // 이벤트 호출
    InventoryUpdated.Broadcast(SlotIndex);
}

void UUGFInventoryComponent::RemoveInventorySlot(int32 SlotIndex)
{
    // 유효성 검사
    if (SlotIndex < 0) return;

    // 이미 비어있는 경우
    if (!InventorySlots.Contains(SlotIndex)) return;

    // 정리할 슬롯 가져오기
    const auto& InventorySlotToClear = InventorySlots[SlotIndex];

    // 캐시 업데이트
    RemoveCachedQuantityMap(InventorySlotToClear.ItemDefinition, InventorySlotToClear.Quantity);
    RemoveCachedIndicesMap(InventorySlotToClear.ItemDefinition, SlotIndex);

    // 슬롯 제거
    InventorySlots.Remove(SlotIndex);

    // 이벤트 호출
    InventoryUpdated.Broadcast(SlotIndex);
}

void UUGFInventoryComponent::AddQuantityToSlot(int32 SlotIndex, int32 QuantityToAdd)
{
    // 유효성 검사
    if (SlotIndex < 0 || QuantityToAdd <= 0) return;

    // 존재하지 않는 경우
    if (!InventorySlots.Contains(SlotIndex)) return;

    // 슬롯 업데이트
    auto& InventorySlot = InventorySlots[SlotIndex];
    InventorySlot.Quantity += QuantityToAdd;

    // 캐시 업데이트
    AddCachedQuantityMap(InventorySlot.ItemDefinition, QuantityToAdd);

    // 이벤트 호출
    InventoryUpdated.Broadcast(SlotIndex);
}

void UUGFInventoryComponent::RemoveQuantityFromSlot(int32 SlotIndex, int32 QuantityToRemove)
{
    // 유효성 검사
    if (SlotIndex < 0 || QuantityToRemove <= 0) return;

    // 존재하지 않는 경우
    if (!InventorySlots.Contains(SlotIndex)) return;

    // 슬롯 업데이트
    auto& InventorySlot = InventorySlots[SlotIndex];
    if (InventorySlot.Quantity == QuantityToRemove)
    {
        RemoveInventorySlot(SlotIndex);
        return;
    }
    InventorySlot.Quantity -= QuantityToRemove;

    // 캐시 업데이트
    RemoveCachedQuantityMap(InventorySlot.ItemDefinition, QuantityToRemove);

    // 이벤트 호출
    InventoryUpdated.Broadcast(SlotIndex);
}
