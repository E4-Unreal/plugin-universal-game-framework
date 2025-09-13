// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/InventoryComponent.h"

#include "InventorySystemFunctionLibrary.h"
#include "Data/ItemInstance.h"
#include "Interfaces/DataDefinitionInterface.h"
#include "Interfaces/ItemDataInterface.h"

UInventoryComponent::UInventoryComponent()
{

}

void UInventoryComponent::BeginPlay()
{
    Super::BeginPlay();

    AddDefaultItems();
}

bool UInventoryComponent::HasContent(UDataInstanceBase* InContent) const
{
    if (CheckContent(InContent))
    {
        const int32 InQuantity = IItemInstanceInterface::Execute_GetQuantity(InContent);
        int32 OwnedQuantity = GetItemQuantity(GetDataFromContent(InContent));

        return OwnedQuantity >= InQuantity;
    }

    return false;
}

bool UInventoryComponent::AddContent(UDataInstanceBase* InContent)
{
    // 실행 가능 여부 확인
    if (!CheckContent(InContent)) return false;

    UDataAsset* InData = GetDataFromContent(InContent);
    int32 Quantity = IItemInstanceInterface::Execute_GetQuantity(InContent);
    const int32 MaxStack = IItemDataInterface::Execute_GetMaxStack(InData);

    // 기존 인벤토리 슬롯 채우기
    for (const auto& [Index, Content] : SlotMap)
    {
        if (Content == nullptr || Content != InContent) continue;

        UDataAsset* SlotData = GetDataFromContent(Content);
        const int32 SlotMaxStack = IItemDataInterface::Execute_GetMaxStack(SlotData);
        const int32 SlotQuantity = IItemInstanceInterface::Execute_GetQuantity(Content);
        const int32 SlotCapacity = SlotMaxStack - SlotQuantity;

        const int32 QuantityToAdd = FMath::Min(Quantity, SlotCapacity);
        Quantity -= QuantityToAdd;

        SetSlotQuantity(Index, SlotQuantity + QuantityToAdd);

        if (Quantity <= 0) return true;
    }

    // 새로운 인벤토리 슬롯 추가

    while (Quantity > 0 && DoesSlotExist(GetEmptySlotIndex(InContent)))
    {
        const int32 EmptySlotIndex = GetEmptySlotIndex(InContent);

        int32 QuantityToAdd = FMath::Min(Quantity, MaxStack);
        Quantity -= QuantityToAdd;

        auto NewContent = IDataDefinitionInterface::Execute_CreateInstance(InData);
        IItemInstanceInterface::Execute_SetQuantity(NewContent, QuantityToAdd);
        SetContent(EmptySlotIndex, NewContent);
    }

    return true;
}

bool UInventoryComponent::RemoveContent(UDataInstanceBase* InContent)
{
    // 실행 가능 여부 확인
    if (!HasContent(InContent)) return false;

    UDataAsset* InData = GetDataFromContent(InContent);
    int32 InQuantity = IItemInstanceInterface::Execute_GetQuantity(InContent);

    // 인벤토리 조회 및 아이템 제거
    for (const auto& [Index, Content] : SlotMap)
    {
        if (GetDataFromContent(Content) != InData) continue;

        const int32 SlotQuantity = IItemInstanceInterface::Execute_GetQuantity(Content);

        const int32 QuantityToRemove = FMath::Min(InQuantity, SlotQuantity);
        InQuantity -= QuantityToRemove;

        SetSlotQuantity(Index, SlotQuantity - QuantityToRemove);

        if (InQuantity <= 0) break;
    }

    return true;
}

void UInventoryComponent::SwapContent(USlotManagerComponentBase* Source, int32 SourceIndex,
    USlotManagerComponentBase* Destination, int32 DestinationIndex)
{
    // Fill
    if (Source && Destination && !Source->IsSlotEmpty(SourceIndex) && !Destination->IsSlotEmpty(DestinationIndex) && Source == Destination)
    {
        auto SourceContent = Source->GetContent(SourceIndex);
        UDataAsset* SourceData = GetDataFromContent(SourceContent);

        auto DestinationContent = Destination->GetContent(DestinationIndex);
        UDataAsset* DestinationData = GetDataFromContent(DestinationContent);

        if (SourceData == DestinationData)
        {
            const int32 SourceSlotQuantity = IItemInstanceInterface::Execute_GetQuantity(SourceContent);
            const int32 DestinationSlotMaxStack = IItemDataInterface::Execute_GetMaxStack(DestinationData);
            const int32 DestinationSlotQuantity = IItemInstanceInterface::Execute_GetQuantity(DestinationContent);
            const int32 DestinationSlotCapacity = DestinationSlotMaxStack - DestinationSlotQuantity;
            int32 QuantityToMove = FMath::Min(SourceSlotQuantity, DestinationSlotCapacity);

            SetSlotQuantity(SourceIndex, SourceSlotQuantity - QuantityToMove);
            SetSlotQuantity(DestinationIndex, DestinationSlotQuantity + QuantityToMove);

            return;
        }
    }

    Super::SwapContent(Source, SourceIndex, Destination, DestinationIndex);
}

void UInventoryComponent::AddItemFromData(UDataAsset* NewData, int32 Quantity)
{
    if (CheckData(NewData))
    {
        auto NewContent = IDataDefinitionInterface::Execute_CreateInstance(NewData);
        IItemInstanceInterface::Execute_SetQuantity(NewContent, Quantity);
        AddContent(NewContent);
    }
}

bool UInventoryComponent::SetSlotQuantity(int32 SlotIndex, int32 NewQuantity)
{
    auto OldContent = GetContent(SlotIndex);
    if (CheckContent(OldContent))
    {
        if (NewQuantity <= 0)
        {
            SetContent(SlotIndex, nullptr);
        }
        else
        {
            IItemInstanceInterface::Execute_SetQuantity(OldContent, NewQuantity);
        }

        OnSlotUpdated.Broadcast(SlotIndex);

        return true;
    }

    return false;
}

void UInventoryComponent::DropItemFromSlot(int32 SlotIndex, int32 Quantity)
{
    if (bool bCanDrop = !IsSlotEmpty(SlotIndex); !bCanDrop) return;

    const auto Content = GetContent(SlotIndex);
    UDataAsset* Data = GetDataFromContent(Content);
    const int32 SlotQuantity = IItemInstanceInterface::Execute_GetQuantity(Content);

    if (SlotQuantity < Quantity) return;

    auto NewItemInstance = IDataDefinitionInterface::Execute_CreateInstance(Data);
    IItemInstanceInterface::Execute_SetQuantity(NewItemInstance, Quantity);

    TArray<UDataInstanceBase*> InventoryItemsToDrop = { NewItemInstance };

    AActor* SpawnedItemActor = UInventorySystemFunctionLibrary::SpawnItemPackageActor(GetOwner(), ItemActorClass, InventoryItemsToDrop, DropItemOffset);
    if (!SpawnedItemActor) return;

    SetSlotQuantity(SlotIndex, SlotQuantity - Quantity);
}

int32 UInventoryComponent::GetItemQuantity(UDataAsset* Item) const
{
    if (!CheckData(Item)) return 0;

    int32 Quantity = 0;
    for (const auto& [Index, Content] : Slots)
    {
        if (GetDataFromContent(Content) == Item)
        {
            Quantity += IItemInstanceInterface::Execute_GetQuantity(Content);
        }
    }

    return Quantity;
}

int32 UInventoryComponent::GetItemCapacity(UDataAsset* Item) const
{
    int32 Capacity = 0;

    if (CheckData(Item))
    {
        int32 EmptySlotNum = MaxSlotNum - Slots.Num();
        Capacity = EmptySlotNum * IItemDataInterface::Execute_GetMaxStack(Item);
        for (const auto& [Index, Content] : Slots)
        {
            if (GetDataFromContent(Content) == Item)
            {
                const int32 SlotQuantity = IItemInstanceInterface::Execute_GetQuantity(Content);
                const int32 SlotMaxStack = IItemDataInterface::Execute_GetMaxStack(Item);
                const int32 SlotCapacity = SlotMaxStack - SlotQuantity;
                Capacity += SlotCapacity;
            }
        }
    }

    return Capacity;
}

void UInventoryComponent::AddDefaultItems()
{
    for (const auto& DefaultItem : StartupItems)
    {
        AddContent(DefaultItem);
    }
}
