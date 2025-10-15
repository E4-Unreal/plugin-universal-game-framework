// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/EquipmentManagerComponent.h"

#include "Components/SocketManagerComponent.h"
#include "DataManager/Public/Data/DataDefinitionBase.h"
#include "DataManager/Public/Data/DataInstanceBase.h"
#include "Interfaces/EquipmentDataInterface.h"
#include "Interfaces/EquipmentInstanceInterface.h"

void UEquipmentManagerComponent::OnRegister()
{
    Super::OnRegister();

    FindSocketManager();
    CreateSlots();
}

void UEquipmentManagerComponent::SetSocketManager(USocketManagerComponent* NewSocketManager)
{
    SocketManager = NewSocketManager;
}

bool UEquipmentManagerComponent::HasSlot(FEquipmentSlotIndex InSlotIndex) const
{
    return SlotIndexMap.Contains(InSlotIndex);
}

const FEquipmentSlot& UEquipmentManagerComponent::GetSlot(FEquipmentSlotIndex InSlotIndex) const
{
    return HasSlot(InSlotIndex) ? Slots[SlotIndexMap[InSlotIndex]] : FEquipmentSlot::EmptySlot;
}

bool UEquipmentManagerComponent::IsSlotEmpty(FEquipmentSlotIndex InSlotIndex) const
{
    if (HasSlot(InSlotIndex))
    {
        const auto& Slot = GetSlot(InSlotIndex);
        return Slot.IsEmpty();
    }

    return false;
}

FEquipmentSlotIndex UEquipmentManagerComponent::GetEmptySlotIndex(FGameplayTag Type) const
{
    FEquipmentSlotIndex SlotIndex;
    for (const auto& Slot : Slots)
    {
        if (Slot.Index.Type == Type && Slot.IsEmpty())
        {
            SlotIndex = Slot.Index;
            break;
        }
    }

    return SlotIndex;
}

UDataInstanceBase* UEquipmentManagerComponent::GetEquipment(FEquipmentSlotIndex InSlotIndex) const
{
    UDataInstanceBase* Equipment = nullptr;

    if (HasSlot(InSlotIndex))
    {
        const auto& Slot = GetSlot(InSlotIndex);
        Equipment = Slot.Equipment;
    }

    return Equipment;
}

bool UEquipmentManagerComponent::CanEquip(UDataInstanceBase* NewEquipment, FEquipmentSlotIndex InSlotIndex) const
{
    if (NewEquipment
        && NewEquipment->Implements<UEquipmentInstanceInterface>()
        && NewEquipment->GetDefinition()
        && NewEquipment->GetDefinition()->Implements<UEquipmentDataInterface>())
    {
        if (InSlotIndex.IsValid() && IsSlotEmpty(InSlotIndex))
        {
            return true;
        }
        else
        {
            FGameplayTag Type = IEquipmentDataInterface::Execute_GetEquipmentType(NewEquipment->GetDefinition());
            FEquipmentSlotIndex EmptySlotIndex = GetEmptySlotIndex(Type);

            return EmptySlotIndex.IsValid();
        }
    }

    return false;
}

void UEquipmentManagerComponent::Equip(UDataInstanceBase* NewEquipment, FEquipmentSlotIndex InSlotIndex)
{
    if (!CanEquip(NewEquipment, InSlotIndex)) return;

    if (!InSlotIndex.IsValid())
    {
        FGameplayTag Type = IEquipmentDataInterface::Execute_GetEquipmentType(NewEquipment->GetDefinition());
        InSlotIndex = GetEmptySlotIndex(Type);
    }

    auto& Slot = const_cast<FEquipmentSlot&>(GetSlot(InSlotIndex));

    Slot.Equipment = NewEquipment;
    OnEquip(Slot);
}

UDataInstanceBase* UEquipmentManagerComponent::UnEquip(FEquipmentSlotIndex InSlotIndex)
{
    if (IsSlotEmpty(InSlotIndex)) return nullptr;

    auto& Slot = const_cast<FEquipmentSlot&>(GetSlot(InSlotIndex));
    auto OldEquipment = Slot.Equipment;

    OnUnEquip(Slot);
    Slot.Equipment = nullptr;

    return OldEquipment;
}

void UEquipmentManagerComponent::FindSocketManager()
{
    if (SocketManager.IsValid()) return;

    SocketManager = Cast<USocketManagerComponent>(GetOwner()->GetComponentByClass<USocketManagerComponent>());
}

void UEquipmentManagerComponent::CreateSlots()
{
    for (const auto& SlotConfig : SlotConfigs)
    {
        for (int32 Index = 0; Index < SlotConfig.SocketTags.Num(); ++Index)
        {
            FEquipmentSlotIndex NewSlotIndex;
            NewSlotIndex.Type = SlotConfig.Type;
            NewSlotIndex.Index = Index;

            FEquipmentSlot NewSlot;
            NewSlot.Index = NewSlotIndex;
            NewSlot.SocketTag = SlotConfig.SocketTags[Index];

            SlotIndexMap.Emplace(NewSlotIndex, Slots.Num());
            Slots.Emplace(NewSlot);
        }
    }
}

void UEquipmentManagerComponent::OnEquip(const FEquipmentSlot& Slot)
{
    if (SocketManager.IsValid())
    {
        auto SocketTag = Slot.SocketTag;

        auto Data = Slot.Equipment->GetDefinition();
        auto SocketName = IEquipmentDataInterface::Execute_GetSocketName(Data);
        auto StaticMesh = IEquipmentDataInterface::Execute_GetStaticMesh(Data);
        auto SkeletalMesh = IEquipmentDataInterface::Execute_GetSkeletalMesh(Data);

        if (!SkeletalMesh.IsNull())
        {
            SocketManager->SetSkeletalMesh(SkeletalMesh.LoadSynchronous(), SocketTag, SocketName);
        }
        else if (!StaticMesh.IsNull())
        {
            SocketManager->SetStaticMesh(StaticMesh.LoadSynchronous(), SocketTag, SocketName);
        }
    }
}

void UEquipmentManagerComponent::OnUnEquip(const FEquipmentSlot& Slot)
{
    if (SocketManager.IsValid())
    {
        SocketManager->ResetSlot(Slot.SocketTag);
    }
}
