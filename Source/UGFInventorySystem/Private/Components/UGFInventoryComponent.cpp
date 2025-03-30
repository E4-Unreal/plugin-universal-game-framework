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

    // ItemQuantityMap 업데이트
    int32 AddedQuantity = Item.Quantity - Overflow;
    if (AddedQuantity > 0) AddItemQuantity(Item.ItemDefinition, AddedQuantity);

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

    // ItemQuantityMap 업데이트
    int32 QuantityToRemove = Item.Quantity - Underflow;
    if (QuantityToRemove > 0)
    {
        RemoveItemQuantity(Item.ItemDefinition, QuantityToRemove);
        SortInventorySlots();
    }

    LOG(Log, TEXT("Try remove item(%s) > Quantity: %d, Underflow: %d"), *Item.ItemDefinition->GetDisplayName().ToString(), Item.Quantity, Underflow)
}

void UUGFInventoryComponent::SwapInventorySlot(int32 SourceIndex, int32 TargetIndex)
{
    LOG_TODO
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
    if (!ItemInventoryIndicesMap.Contains(ItemDefinition)) return;

    // 인벤토리 전용 아이템 데이터 가져오기
    auto InventoryItemConfig = UUGFInventoryItemConfig::GetFromItemDefinition(ItemDefinition);
    const auto& Data = InventoryItemConfig->GetData();
    int32 MaxStack = Data.MaxStack;

    // 기존 인벤토리 슬롯 채우기
    const auto& InventoryIndices = ItemInventoryIndicesMap[ItemDefinition].Indices;
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
        SetInventorySlot(InventoryIndex, ItemDefinition, InventorySlot.Quantity + QuantityToAdd);

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
        SetInventorySlot(Index, ItemDefinition, QuantityToAdd);

        if (Overflow <= 0) break;
    }

    // 인벤토리 슬롯 정렬
    SortInventorySlots();
}

void UUGFInventoryComponent::RemoveInventorySlots(UUGFItemDefinition* ItemDefinition, int32& Underflow)
{
    check(ItemDefinition != nullptr);

    if (!ItemInventoryIndicesMap.Contains(ItemDefinition)) return;

    TArray<int32> InventoryIndices = ItemInventoryIndicesMap[ItemDefinition].Indices.Array();
    for (int32 InventoryIndex : InventoryIndices)
    {
        // 기존 인벤토리 슬롯에서 제거할 수량 계산
        auto& InventorySlot = InventorySlots[InventoryIndex];
        int32 QuantityToRemove = InventorySlot.Quantity > Underflow ? Underflow : InventorySlot.Quantity;
        Underflow -= QuantityToRemove;

        // 기존 인벤토리 슬롯에서 수량 제거
        SetInventorySlot(InventoryIndex, ItemDefinition, InventorySlot.Quantity - QuantityToRemove);

        if (InventorySlot.Quantity <= 0)
        {
            InventorySlots.Remove(InventoryIndex);
            RemoveInventoryIndex(ItemDefinition, InventoryIndex);
        }

        if (Underflow == 0) break;
    }

    SortInventorySlots();
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

void UUGFInventoryComponent::SetInventorySlot(int32 Index, UUGFItemDefinition* ItemDefinition, int32 ItemQuantity)
{
    int32 OldItemQuantity = 0;
    int32 NewItemQuantity = ItemQuantity;
    if (InventorySlots.Contains(Index))
    {
        // 기존 인벤토리 슬롯 가져오기
        auto& InventorySlot = InventorySlots[Index];
        check(InventorySlot.ItemDefinition == ItemDefinition);

        // 기존 아이템 수량 저장
        OldItemQuantity = InventorySlot.Quantity;

        // 아이템 수량 변경 혹은 인벤토리 슬롯 비우기
        if (NewItemQuantity <= 0)
        {
            // 기존 인벤토리 슬롯 제거 및 캐시 업데이트
            RemoveInventoryIndex(ItemDefinition, Index);
            InventorySlots.Remove(Index);
        }
        else
        {
            InventorySlot.Quantity = NewItemQuantity;
        }
    }
    else if (NewItemQuantity > 0)
    {
        // 새로운 인벤토리 슬롯 생성
        FUGFInventorySlot NewInventorySlot;
        NewInventorySlot.Index = Index;
        NewInventorySlot.ItemDefinition = ItemDefinition;
        NewInventorySlot.Quantity = NewItemQuantity;

        // 새로운 인벤토리 슬롯 추가 및 캐시 업데이트
        InventorySlots.Emplace(Index, NewInventorySlot);
        AddInventoryIndex(ItemDefinition, Index);
    }

    LOG(Log, TEXT("InventorySlots[%d](%s): %d > %d"), Index, *ItemDefinition->GetDisplayName().ToString(), OldItemQuantity, NewItemQuantity)

    // 이벤트 호출
    InventoryUpdated.Broadcast(Index);
}

void UUGFInventoryComponent::AddDefaultItems()
{
    for (const auto& DefaultItem : DefaultItems)
    {
        int32 Overflow;
        AddItem(DefaultItem, Overflow);
    }
}
