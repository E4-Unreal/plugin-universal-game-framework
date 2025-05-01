// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/InventoryComponent.h"

#include "InventorySystemFunctionLibrary.h"
#include "Interfaces/InventoryItemDataInterface.h"
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

bool UInventoryComponent::HasItem(const TScriptInterface<IInventoryItemDataInterface>& Item, int32 Quantity) const
{
    if(!IsValidItem(Item, Quantity)) return false;

    int32 ItemQuantity = GetItemQuantity(Item);
    return ItemQuantity >= Quantity;
}

bool UInventoryComponent::AddItem(const TScriptInterface<IInventoryItemDataInterface>& Item, int32 Quantity)
{
    // 실행 가능 여부 확인
    if (!IsValidItem(Item, Quantity)) return false;

    // 기존 인벤토리 슬롯 채우기
    TSet<int32> ExistingIndices;
    ExistingIndices.Reserve(InventorySlots.Num());
    for (const auto& InventorySlot : InventorySlots)
    {
        ExistingIndices.Emplace(InventorySlot.Index);
        if (InventorySlot.Item != Item) continue;

        int32 QuantityToAdd = FMath::Min(Quantity, InventorySlot.GetCapacity());
        Quantity -= QuantityToAdd;
        SetInventorySlotQuantity(InventorySlot.Index, InventorySlot.Quantity + QuantityToAdd);

        if (Quantity <= 0) return true;
    }

    // 새로운 인벤토리 슬롯 추가
    for (int32 Index = 0; Index < MaxSlotNum; ++Index)
    {
        if (ExistingIndices.Contains(Index)) continue;

        int32 QuantityToAdd = FMath::Min(Quantity, GetInventoryItemData(Item).MaxStack);
        Quantity -= QuantityToAdd;

        FInventorySlot NewInventorySlot;
        NewInventorySlot.Index = Index;
        NewInventorySlot.Item = Item;
        NewInventorySlot.Quantity = QuantityToAdd;

        SetInventorySlot(NewInventorySlot);

        if (Quantity <= 0) return true;
    }

    check(Quantity <= 0)
    return true;
}

bool UInventoryComponent::RemoveItem(const TScriptInterface<IInventoryItemDataInterface>& Item, int32 Quantity)
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

bool UInventoryComponent::SetInventorySlotQuantity(int32 SlotIndex, int32 NewQuantity)
{
    auto InventorySlot = InventorySlots.FindByKey(SlotIndex);
    if (bool bCanSet = InventorySlot && InventorySlot->GetInventoryItemData().MaxStack >= NewQuantity; !bCanSet) return false;

    if (NewQuantity <= 0)
    {
        InventorySlots.RemoveSingle(*InventorySlot);
    }
    else
    {
        InventorySlot->Quantity = NewQuantity;
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
        int32 QuantityToMove = FMath::Min(SourceInventorySlot.Quantity, DestinationInventorySlot.GetCapacity());
        SetInventorySlotQuantity(SourceIndex, SourceInventorySlot.Quantity - QuantityToMove);
        OtherInventoryComponent->SetInventorySlotQuantity(DestinationIndex, DestinationInventorySlot.Quantity + QuantityToMove);
    }
}

void UInventoryComponent::DropItemFromSlot(int32 SlotIndex, int32 Quantity)
{
    if (bool bCanDrop = !IsSlotEmpty(SlotIndex); !bCanDrop) return;

    const auto& InventorySlot = GetInventorySlot(SlotIndex);
    if (InventorySlot.Quantity < Quantity) return;

    TArray<FInventoryItem> InventoryItemsToDrop = { FInventoryItem{ InventorySlot.Item, Quantity } };
    AActor* SpawnedItemActor = UInventorySystemFunctionLibrary::SpawnItemActor(GetOwner(), ItemActorClass, InventoryItemsToDrop, DropItemOffset);
    if (!SpawnedItemActor) return;

    SetInventorySlotQuantity(SlotIndex, InventorySlot.Quantity - Quantity);
}

int32 UInventoryComponent::GetItemQuantity(const TScriptInterface<IInventoryItemDataInterface>& Item) const
{
    if (!Item) return 0;

    int32 Quantity = 0;
    for (const auto& InventorySlot : InventorySlots)
    {
        if (Item == InventorySlot.Item.GetObject())
        {
            Quantity += InventorySlot.Quantity;
        }
    }

    return Quantity;
}

int32 UInventoryComponent::GetItemCapacity(const TScriptInterface<IInventoryItemDataInterface>& Item) const
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

void UInventoryComponent::AddDefaultItems()
{
    for (const auto& DefaultItem : DefaultItems)
    {
        AddItem(DefaultItem.Item, DefaultItem.Quantity);
    }
}

bool UInventoryComponent::IsValidItem(const TScriptInterface<IInventoryItemDataInterface>& Item, int32 Quantity)
{
    const auto& InventoryItemData = GetInventoryItemData(Item);
    UE_LOG(LogTemp, Error, TEXT("%d"), InventoryItemData.MaxStack)
    return InventoryItemData.IsValid() && Quantity > 0;
}

const FInventoryItemData UInventoryComponent::GetInventoryItemData(const TScriptInterface<IInventoryItemDataInterface>& Item)
{
    return Item.GetObject() ? IInventoryItemDataInterface::Execute_GetInventoryItemData(Item.GetObject()) : FInventoryItemData::Empty;
}

void UInventoryComponent::OnRep_InventorySlots(const TArray<FInventorySlot>& OldInventorySlots)
{
}
