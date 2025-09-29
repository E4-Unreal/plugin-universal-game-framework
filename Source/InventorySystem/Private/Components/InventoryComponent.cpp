// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/InventoryComponent.h"

#include "InventorySystemFunctionLibrary.h"
#include "Data/ItemInstance.h"
#include "FunctionLibraries/DataManagerFunctionLibrary.h"
#include "Interfaces/DataInterface.h"
#include "Interfaces/ItemDataInterface.h"
#include "Settings/InventorySystemSettings.h"

UInventoryComponent::UInventoryComponent()
{
    UsingDataInterfaces.Emplace(UItemDataInterface::StaticClass());
    UsingInstanceDataInterfaces.Emplace(UItemInstanceInterface::StaticClass());
}

void UInventoryComponent::BeginPlay()
{
    Super::BeginPlay();

    AddDefaultItems();
}

bool UInventoryComponent::HasContent(UObject* InContent) const
{
    if (CheckContent(InContent))
    {
        const int32 InQuantity = GetQuantity(InContent);
        int32 OwnedQuantity = GetItemQuantity(GetDataFromContent(InContent));

        return OwnedQuantity >= InQuantity;
    }

    return false;
}

bool UInventoryComponent::AddContent(UObject* InContent)
{
    // 실행 가능 여부 확인
    if (!CheckContent(InContent)) return false;

    UDataAsset* InData = GetDataFromContent(InContent);
    int32 Quantity = GetQuantity(InContent);
    const int32 MaxStack = GetMaxStack(InData);

    // 기존 인벤토리 슬롯 채우기
    for (const auto& [Index, Content] : SlotMap)
    {
        if (Content == nullptr || Content != InContent) continue;

        UDataAsset* SlotData = GetDataFromContent(Content);
        const int32 SlotMaxStack = GetMaxStack(SlotData);
        const int32 SlotQuantity = GetQuantity(Content);
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

        auto NewContent = CreateItemInstance(InData);
        SetQuantity(NewContent, QuantityToAdd);
        SetContent(EmptySlotIndex, NewContent);
    }

    return true;
}

bool UInventoryComponent::RemoveContent(UObject* InContent)
{
    // 실행 가능 여부 확인
    if (!HasContent(InContent)) return false;

    UDataAsset* InData = GetDataFromContent(InContent);
    int32 InQuantity = GetQuantity(InContent);

    // 인벤토리 조회 및 아이템 제거
    for (const auto& [Index, Content] : SlotMap)
    {
        if (GetDataFromContent(Content) != InData) continue;

        const int32 SlotQuantity = GetQuantity(Content);

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
            const int32 SourceSlotQuantity = GetQuantity(SourceContent);
            const int32 DestinationSlotMaxStack = GetMaxStack(DestinationData);
            const int32 DestinationSlotQuantity = GetQuantity(DestinationContent);
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
        auto NewContent = CreateItemInstance(NewData);
        SetQuantity(NewContent, Quantity);
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
            SetQuantity(OldContent, NewQuantity);
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
    const int32 SlotQuantity = GetQuantity(Content);

    if (SlotQuantity < Quantity) return;

    auto NewItemInstance = CreateItemInstance(Data);
    SetQuantity(NewItemInstance, Quantity);

    TArray<UObject*> InventoryItemsToDrop = { NewItemInstance };

    AActor* SpawnedItemActor = UInventorySystemFunctionLibrary::SpawnItemPackageActor(GetOwner(), GetItemActorClass(), InventoryItemsToDrop, DropItemOffset);
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
            Quantity += GetQuantity(Content);
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
        Capacity = EmptySlotNum * GetMaxStack(Item);
        for (const auto& [Index, Content] : Slots)
        {
            if (GetDataFromContent(Content) == Item)
            {
                const int32 SlotQuantity = GetQuantity(Content);
                const int32 SlotMaxStack = GetMaxStack(Item);
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

UDataAsset* UInventoryComponent::GetItemData(UObject* DataObject)
{
    return UDataManagerFunctionLibrary::GetDataByInterface<UItemDataInterface>(DataObject);
}

int32 UInventoryComponent::GetMaxStack(UObject* DataObject)
{
    auto ItemData = GetItemData(DataObject);

    return ItemData ? GetMaxStack(ItemData) : 0;
}

FGameplayTag UInventoryComponent::GetItemType(UObject* DataObject)
{
    auto ItemData = GetItemData(DataObject);

    return ItemData ? IItemDataInterface::Execute_GetItemType(ItemData) : FGameplayTag::EmptyTag;
}

UObject* UInventoryComponent::CreateItemInstance(UDataAsset* Data) const
{
    auto ItemInstance = UDataManagerFunctionLibrary::CreateInstanceData(Data);

    return CheckContent(ItemInstance) ? ItemInstance : nullptr;
}

UObject* UInventoryComponent::GetItemInstance(UObject* InstanceData)
{
    return UDataManagerFunctionLibrary::GetInstanceDataByInterface<UItemInstanceInterface>(InstanceData);
}

int32 UInventoryComponent::GetQuantity(UObject* InstanceData)
{
    auto ItemInstance = GetItemInstance(InstanceData);

    return ItemInstance ? GetQuantity(ItemInstance) : 0;
}

void UInventoryComponent::SetQuantity(UObject* InstanceData, int32 NewQuantity)
{
    if (auto ItemInstance = GetItemInstance(InstanceData))
    {
        SetQuantity(ItemInstance, NewQuantity);
    }
}
