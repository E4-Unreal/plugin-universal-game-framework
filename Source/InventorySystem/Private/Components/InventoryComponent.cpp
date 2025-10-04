// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/InventoryComponent.h"

#include "FunctionLibraries/InventorySystemFunctionLibrary.h"
#include "Data/ItemInstance.h"
#include "FunctionLibraries/ItemDataFunctionLibrary.h"
#include "Settings/InventorySystemSettings.h"

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
        const int32 InQuantity = UItemDataFunctionLibrary::GetQuantity(InContent);
        int32 OwnedQuantity = GetItemQuantity(InContent->Definition);

        return OwnedQuantity >= InQuantity;
    }

    return false;
}

bool UInventoryComponent::AddContent(UDataInstanceBase* InContent)
{
    // 실행 가능 여부 확인
    if (!CheckContent(InContent)) return false;

    int32 Quantity = UItemDataFunctionLibrary::GetQuantity(InContent);
    const int32 MaxStack = UItemDataFunctionLibrary::GetMaxStack(InContent->Definition);

    // 기존 인벤토리 슬롯 채우기
    for (const auto& [Index, Content] : SlotMap)
    {
        if (Content == nullptr || Content != InContent) continue;

        const int32 SlotMaxStack = UItemDataFunctionLibrary::GetMaxStack(Content->Definition);
        const int32 SlotQuantity = UItemDataFunctionLibrary::GetQuantity(Content);
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

        auto NewContent = UItemDataFunctionLibrary::CreateItemInstance(InContent->Definition);
        UItemDataFunctionLibrary::SetQuantity(NewContent, QuantityToAdd);
        SetContent(EmptySlotIndex, NewContent);
    }

    return true;
}

bool UInventoryComponent::RemoveContent(UDataInstanceBase* InContent)
{
    // 실행 가능 여부 확인
    if (!HasContent(InContent)) return false;

    int32 InQuantity = UItemDataFunctionLibrary::GetQuantity(InContent);

    // 인벤토리 조회 및 아이템 제거
    for (const auto& [Index, Content] : SlotMap)
    {
        if (Content == nullptr || Content->Definition != InContent->Definition) continue;

        const int32 SlotQuantity = UItemDataFunctionLibrary::GetQuantity(Content);

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
        auto SourceData = SourceContent->Definition;

        auto DestinationContent = Destination->GetContent(DestinationIndex);
        auto DestinationData = DestinationContent->Definition;

        if (SourceData == DestinationData)
        {
            const int32 SourceSlotQuantity = UItemDataFunctionLibrary::GetQuantity(SourceContent);
            const int32 DestinationSlotMaxStack = UItemDataFunctionLibrary::GetMaxStack(DestinationData);
            const int32 DestinationSlotQuantity = UItemDataFunctionLibrary::GetQuantity(DestinationContent);
            const int32 DestinationSlotCapacity = DestinationSlotMaxStack - DestinationSlotQuantity;
            int32 QuantityToMove = FMath::Min(SourceSlotQuantity, DestinationSlotCapacity);

            SetSlotQuantity(SourceIndex, SourceSlotQuantity - QuantityToMove);
            SetSlotQuantity(DestinationIndex, DestinationSlotQuantity + QuantityToMove);

            return;
        }
    }

    Super::SwapContent(Source, SourceIndex, Destination, DestinationIndex);
}

void UInventoryComponent::AddItemFromData(UDataDefinitionBase* NewData, int32 Quantity)
{
    if (CheckData(NewData))
    {
        auto NewContent = UItemDataFunctionLibrary::CreateItemInstance(NewData);
        UItemDataFunctionLibrary::SetQuantity(NewContent, Quantity);
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
            UItemDataFunctionLibrary::SetQuantity(OldContent, NewQuantity);
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
    const int32 SlotQuantity = UItemDataFunctionLibrary::GetQuantity(Content);

    if (SlotQuantity < Quantity) return;

    auto NewItemInstance = UItemDataFunctionLibrary::CreateItemInstance(Content->Definition);
    UItemDataFunctionLibrary::SetQuantity(NewItemInstance, Quantity);

    TArray<UDataInstanceBase*> InventoryItemsToDrop = { NewItemInstance };

    AActor* SpawnedItemActor = UInventorySystemFunctionLibrary::SpawnItemPackageActor(GetOwner(), GetItemActorClass(), InventoryItemsToDrop, DropItemOffset);
    if (!SpawnedItemActor) return;

    SetSlotQuantity(SlotIndex, SlotQuantity - Quantity);
}

int32 UInventoryComponent::GetItemQuantity(UDataDefinitionBase* Item) const
{
    if (!CheckData(Item)) return 0;

    int32 Quantity = 0;
    for (const auto& [Index, Content] : Slots)
    {
        if (Content && Content->Definition == Item)
        {
            Quantity += UItemDataFunctionLibrary::GetQuantity(Content);
        }
    }

    return Quantity;
}

int32 UInventoryComponent::GetItemCapacity(UDataDefinitionBase* Item) const
{
    int32 Capacity = 0;

    if (CheckData(Item))
    {
        int32 EmptySlotNum = MaxSlotNum - Slots.Num();
        Capacity = EmptySlotNum * UItemDataFunctionLibrary::GetMaxStack(Item);
        for (const auto& [Index, Content] : Slots)
        {
            if (Content->Definition == Item)
            {
                const int32 SlotQuantity = UItemDataFunctionLibrary::GetQuantity(Content);
                const int32 SlotMaxStack = UItemDataFunctionLibrary::GetMaxStack(Item);
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

TSubclassOf<AActor> UInventoryComponent::GetItemActorClass() const
{
    return ItemActorClass ? ItemActorClass : UInventorySystemSettings::Get()->GetDefaultItemActorClass();
}
