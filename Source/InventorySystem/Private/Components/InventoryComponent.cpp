// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/InventoryComponent.h"

#include "Interfaces/InventoryItemDataInterface.h"
#include "Net/UnrealNetwork.h"

UInventoryComponent::UInventoryComponent()
{
    SetIsReplicatedByDefault(true);
}

void UInventoryComponent::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);

    DOREPLIFETIME(ThisClass, InventorySlots)
}

bool UInventoryComponent::HasItem(UObject* Item, int32 Quantity) const
{
    int32 ItemQuantity = GetItemQuantity(Item);
    return ItemQuantity >= Quantity;
}

bool UInventoryComponent::AddItem(UObject* Item, int32 Quantity)
{
    // 실행 가능 여부 확인
    if (bool bCanAdd = Quantity <= GetItemCapacity(Item); !bCanAdd) return false;

    // 기존 인벤토리 슬롯 채우기
    TSet<int32> ExistingIndices;
    ExistingIndices.Reserve(InventorySlots.Num());
    for (const auto& InventorySlot : InventorySlots)
    {
        ExistingIndices.Emplace(InventorySlot.Index);
        if (InventorySlot.Item != Item) continue;

        int32 QuantityToAdd = FMath::Min(Quantity, InventorySlot.GetCapacity());
        Quantity -= QuantityToAdd;

        FInventorySlot NewInventorySlot = InventorySlot;
        NewInventorySlot.Quantity += QuantityToAdd;
        SetInventorySlot(NewInventorySlot);

        if (Quantity <= 0) return true;
    }

    // 새로운 인벤토리 슬롯 추가
    for (int32 Index = 0; Index < MaxSlotNum; ++Index)
    {
        if (ExistingIndices.Contains(Index)) continue;

        FInventorySlot NewInventorySlot;
        NewInventorySlot.Index = Index;
        NewInventorySlot.Item = Item;

        int32 QuantityToAdd = FMath::Min(Quantity, NewInventorySlot.GetCapacity());
        Quantity -= QuantityToAdd;

        NewInventorySlot.Quantity = QuantityToAdd;

        SetInventorySlot(NewInventorySlot);

        if (Quantity <= 0) return true;
    }

    // 정렬
    InventorySlots.Sort();

    check(Quantity <= 0)
    return true;
}

bool UInventoryComponent::RemoveItem(UObject* Item, int32 Quantity)
{
    // 실행 가능 여부 확인
    if (!HasItem(Item, Quantity)) return false;

    // 역순으로 인벤토리 조회 및 아이템 제거
    for (int32 Index = InventorySlots.Num() - 1; Index >= 0; --Index)
    {
        const auto& InventorySlot = InventorySlots[Index];
        if (InventorySlot.Item != Item) continue;

        int32 QuantityToRemove = FMath::Min(Quantity, InventorySlot.Quantity);
        Quantity -= QuantityToRemove;

        if (InventorySlot.Quantity == QuantityToRemove)
        {
            RemoveInventorySlot(Index);
        }
        else
        {
            FInventorySlot NewInventorySlot = InventorySlot;
            NewInventorySlot.Quantity -= QuantityToRemove;
            SetInventorySlot(NewInventorySlot);
        }

        if (Quantity <= 0) return true;
    }

    check(Quantity <= 0)
    return true;
}

bool UInventoryComponent::SetInventorySlot(const FInventorySlot& NewInventorySlot)
{
    if (bool bCanSet = NewInventorySlot.IsValid() && NewInventorySlot.Index < MaxSlotNum; !bCanSet) return false;

    if (auto OldInventorySlotPtr = InventorySlots.FindByKey(NewInventorySlot.Index))
    {
        *OldInventorySlotPtr = NewInventorySlot;
    }
    else
    {
        InventorySlots.Emplace(NewInventorySlot);
    }

    InventoryUpdated.Broadcast(NewInventorySlot.Index);

    return true;
}

void UInventoryComponent::RemoveInventorySlot(int32 SlotIndex)
{
    FInventorySlot* InventorySlot = InventorySlots.FindByKey(SlotIndex);
    if (InventorySlot)
    {
        InventorySlots.Remove(*InventorySlot);
        InventoryUpdated.Broadcast(SlotIndex);
    }
}

void UInventoryComponent::SwapOrFillInventorySlots(int32 SourceIndex, int32 DestinationIndex)
{
    FInventorySlot* SourceInventorySlot = InventorySlots.FindByKey(SourceIndex);
    FInventorySlot* DestinationInventorySlot = InventorySlots.FindByKey(DestinationIndex);

    if (!SourceInventorySlot) return;

    if (DestinationInventorySlot && DestinationInventorySlot->Item == SourceInventorySlot->Item)
    {
        // Fill
        int32 QuantityToAdd = FMath::Min(SourceInventorySlot->Quantity, DestinationInventorySlot->GetCapacity());
        SourceInventorySlot->Quantity -= QuantityToAdd;
        DestinationInventorySlot->Quantity += QuantityToAdd;

        if (SourceInventorySlot->Quantity <= 0) InventorySlots.Remove(*SourceInventorySlot);
    }
    else
    {
        // Swap
        SourceInventorySlot->Index = DestinationIndex;
        if (DestinationInventorySlot) DestinationInventorySlot->Index = SourceIndex;
        InventorySlots.Sort();
    }
}

int32 UInventoryComponent::GetItemQuantity(UObject* Item) const
{
    if (!IsValidItem(Item)) return 0;

    int32 Quantity = 0;
    for (const auto& InventorySlot : InventorySlots)
    {
        if (Item == InventorySlot.Item)
        {
            Quantity += InventorySlot.Quantity;
        }
    }

    return Quantity;
}

int32 UInventoryComponent::GetItemCapacity(UObject* Item) const
{
    const FInventoryItemData InventoryItemData = GetInventoryItemData(Item);
    if (InventoryItemData.IsNotValid()) return 0;

    int32 EmptySlotNum = MaxSlotNum - InventorySlots.Num();
    int32 Capacity = EmptySlotNum * InventoryItemData.MaxStack;
    for (const auto& InventorySlot : InventorySlots)
    {
        if (Item == InventorySlot.Item)
        {
            Capacity += InventorySlot.GetCapacity();
        }
    }

    return Capacity;
}

const FInventorySlot& UInventoryComponent::GetInventorySlot(int32 Index) const
{
    const FInventorySlot* InventorySlot = InventorySlots.FindByKey(Index);

    return InventorySlot ? *InventorySlot : FInventorySlot::EmptySlot;
}

bool UInventoryComponent::IsValidItem(UObject* Item)
{
    return Item && Item->Implements<UInventoryItemDataInterface>();
}

const FInventoryItemData UInventoryComponent::GetInventoryItemData(UObject* Item)
{
    return IsValidItem(Item) ? IInventoryItemDataInterface::Execute_GetInventoryItemData(Item) : FInventoryItemData::Empty;
}

void UInventoryComponent::OnRep_InventorySlots(const TArray<FInventorySlot>& OldInventorySlots)
{
}
