// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/InventoryComponent.h"

#include "InventorySystemFunctionLibrary.h"
#include "Interfaces/ItemDataInterface.h"
#include "Net/UnrealNetwork.h"

UInventoryComponent::UInventoryComponent()
{
    SetIsReplicatedByDefault(true);
}

void UInventoryComponent::BeginPlay()
{
    Super::BeginPlay();

    AddDefaultItems();
}

void UInventoryComponent::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);

    DOREPLIFETIME(ThisClass, InventorySlots)
}

bool UInventoryComponent::HasItem(const FItemInstance& NewItem) const
{
    if(!NewItem.IsValid()) return false;

    int32 ItemQuantity = GetItemQuantity(NewItem.Data);
    return ItemQuantity >= NewItem.Quantity;
}

bool UInventoryComponent::AddItem(const FItemInstance& NewItem)
{
    // 실행 가능 여부 확인
    if (!NewItem.IsValid()) return false;

    int32 Quantity = NewItem.Quantity;
    const int32 MaxStack = NewItem.GetMaxStack();

    // 기존 인벤토리 슬롯 채우기
    TSet<int32> ExistingIndices;
    ExistingIndices.Reserve(InventorySlots.Num());
    for (const auto& InventorySlot : InventorySlots)
    {
        const int32 SlotIndex = InventorySlot.Index;
        const int32 SlotQuantity = InventorySlot.GetQuantity();
        const int32 SlotCapacity = InventorySlot.GetCapacity();

        ExistingIndices.Emplace(SlotIndex);
        if (InventorySlot != NewItem.Data) continue;

        int32 QuantityToAdd = FMath::Min(Quantity, SlotCapacity);
        Quantity -= QuantityToAdd;
        SetInventorySlotQuantity(SlotIndex, SlotQuantity + QuantityToAdd);

        if (Quantity <= 0) return true;
    }

    // 새로운 인벤토리 슬롯 추가
    for (int32 Index = 0; Index < MaxSlotNum; ++Index)
    {
        if (ExistingIndices.Contains(Index)) continue;

        int32 QuantityToAdd = FMath::Min(Quantity, MaxStack);
        Quantity -= QuantityToAdd;

        SetInventorySlot(FInventorySlot(Index, NewItem.Data, QuantityToAdd));

        if (Quantity <= 0) return true;
    }

    check(Quantity <= 0)
    return true;
}

bool UInventoryComponent::RemoveItem(const FItemInstance& NewItem)
{
    // 실행 가능 여부 확인
    if (!HasItem(NewItem)) return false;

    int32 Quantity = NewItem.Quantity;

    // 역순으로 인벤토리 조회 및 아이템 제거
    for (int32 Index = InventorySlots.Num() - 1; Index >= 0; --Index)
    {
        const auto& InventorySlot = InventorySlots[Index];
        const int32 SlotQuantity = InventorySlot.GetQuantity();

        if (InventorySlot.Item != NewItem.Data) continue;

        int32 QuantityToRemove = FMath::Min(Quantity, SlotQuantity);
        Quantity -= QuantityToRemove;

        if (SlotQuantity == QuantityToRemove)
        {
            RemoveInventorySlot(Index);
        }
        else
        {
            FInventorySlot NewInventorySlot = InventorySlot;
            NewInventorySlot.SetQuantity(NewInventorySlot.GetQuantity() - QuantityToRemove);
            SetInventorySlot(NewInventorySlot);
        }

        if (Quantity <= 0) return true;
    }

    check(Quantity <= 0)
    return true;
}

bool UInventoryComponent::SetInventorySlotQuantity(int32 SlotIndex, int32 NewQuantity)
{
    auto InventorySlot = InventorySlots.FindByKey(SlotIndex);
    if (bool bCanSet = InventorySlot && InventorySlot->GetMaxStack() >= NewQuantity; !bCanSet) return false;

    if (NewQuantity <= 0)
    {
        InventorySlots.RemoveSingle(*InventorySlot);
    }
    else
    {
        InventorySlot->SetQuantity(NewQuantity);
    }

    InventoryUpdated.Broadcast(SlotIndex);

    return true;
}

bool UInventoryComponent::SetInventorySlot(const FInventorySlot& NewInventorySlot)
{
    if (bool bCanSet = NewInventorySlot.IsValid() && NewInventorySlot.Index < MaxSlotNum; !bCanSet) return false;

    if (IsSlotEmpty(NewInventorySlot.Index))
    {
        InventorySlots.Emplace(NewInventorySlot);
        InventorySlots.Sort();
    }
    else
    {
        auto& InventorySlot = const_cast<FInventorySlot&>(NewInventorySlot);
        InventorySlot = NewInventorySlot;
    }

    InventoryUpdated.Broadcast(NewInventorySlot.Index);

    return true;
}

void UInventoryComponent::RemoveInventorySlot(int32 SlotIndex)
{
    SetInventorySlotQuantity(SlotIndex, 0);
}

void UInventoryComponent::SwapOrFillInventorySlots(int32 SourceIndex, int32 DestinationIndex, UInventoryComponent* OtherInventoryComponent)
{
    if (!OtherInventoryComponent) OtherInventoryComponent = this;

    auto SourceInventorySlot = GetInventorySlot(SourceIndex);
    auto DestinationInventorySlot = OtherInventoryComponent->GetInventorySlot(DestinationIndex);

    if (IsSlotEmpty(SourceIndex)) return;

    // Move
    if (OtherInventoryComponent->IsSlotEmpty(DestinationIndex))
    {
        RemoveInventorySlot(SourceIndex);

        SourceInventorySlot.Index = DestinationIndex;
        OtherInventoryComponent->SetInventorySlot(SourceInventorySlot);
    }
    // Swap
    else if (SourceInventorySlot.Item != DestinationInventorySlot.Item)
    {
        RemoveInventorySlot(SourceIndex);
        OtherInventoryComponent->RemoveInventorySlot(DestinationIndex);

        SourceInventorySlot.Index = DestinationIndex;
        OtherInventoryComponent->SetInventorySlot(SourceInventorySlot);

        DestinationInventorySlot.Index = SourceIndex;
        SetInventorySlot(DestinationInventorySlot);
    }
    // Fill
    else
    {
        int32 SourceSlotQuantity = SourceInventorySlot.GetQuantity();
        int32 DestinationSlotQuantity = DestinationInventorySlot.GetQuantity();
        int32 QuantityToMove = FMath::Min(SourceSlotQuantity, DestinationInventorySlot.GetCapacity());
        SetInventorySlotQuantity(SourceIndex, SourceSlotQuantity - QuantityToMove);
        OtherInventoryComponent->SetInventorySlotQuantity(DestinationIndex, DestinationSlotQuantity + QuantityToMove);
    }
}

void UInventoryComponent::DropItemFromSlot(int32 SlotIndex, int32 Quantity)
{
    if (bool bCanDrop = !IsSlotEmpty(SlotIndex); !bCanDrop) return;

    const auto& InventorySlot = GetInventorySlot(SlotIndex);
    int32 SlotQuantity = InventorySlot.GetQuantity();

    if (SlotQuantity < Quantity) return;

    TArray<FItemInstance> InventoryItemsToDrop = { InventorySlot.Item };
    AActor* SpawnedItemActor = UInventorySystemFunctionLibrary::SpawnItemActor(GetOwner(), ItemActorClass, InventoryItemsToDrop, DropItemOffset);
    if (!SpawnedItemActor) return;

    SetInventorySlotQuantity(SlotIndex, SlotQuantity - Quantity);
}

int32 UInventoryComponent::GetItemQuantity(const TScriptInterface<IItemDataInterface>& Item) const
{
    if (!Item) return 0;

    int32 Quantity = 0;
    for (const auto& InventorySlot : InventorySlots)
    {
        if (InventorySlot == Item)
        {
            Quantity += InventorySlot.GetQuantity();
        }
    }

    return Quantity;
}

int32 UInventoryComponent::GetItemCapacity(const TScriptInterface<IItemDataInterface>& Item) const
{
    int32 Capacity = 0;

    if (Item)
    {
        int32 EmptySlotNum = MaxSlotNum - InventorySlots.Num();
        Capacity = EmptySlotNum * IItemDataInterface::Execute_GetMaxStack(Item.GetObject());
        for (const auto& InventorySlot : InventorySlots)
        {
            if (InventorySlot == Item)
            {
                Capacity += InventorySlot.GetCapacity();
            }
        }
    }

    return Capacity;
}

const FInventorySlot& UInventoryComponent::GetInventorySlot(int32 Index) const
{
    const FInventorySlot* InventorySlot = InventorySlots.FindByKey(Index);

    return InventorySlot ? *InventorySlot : FInventorySlot::EmptySlot;
}

void UInventoryComponent::AddDefaultItems()
{
    for (const auto& DefaultItem : StartupItems)
    {
        AddItem(FItemInstance(DefaultItem.Data, DefaultItem.Quantity));
    }
}

void UInventoryComponent::OnRep_InventorySlots(const TArray<FInventorySlot>& OldInventorySlots)
{
}
