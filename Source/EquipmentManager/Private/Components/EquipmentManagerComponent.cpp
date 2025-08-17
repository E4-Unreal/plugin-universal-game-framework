// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/EquipmentManagerComponent.h"

#include "Interfaces/EquipmentActorInterface.h"
#include "Interfaces/EquipmentDataInterface.h"


UEquipmentManagerComponent::UEquipmentManagerComponent()
{
    bWantsInitializeComponent = true;
}

void UEquipmentManagerComponent::InitializeComponent()
{
    Super::InitializeComponent();

    CreateSlots();
}

bool UEquipmentManagerComponent::HasSlot(const FEquipmentSlotIndex& SlotIndex) const
{
    if (!SlotIndex.IsValid()) return false;

    for (const auto& Slot : Slots)
    {
        if (Slot.SlotIndex == SlotIndex)
        {
            return true;
        }
    }

    return false;
}

const FEquipmentSlot& UEquipmentManagerComponent::GetSlot(const FEquipmentSlotIndex& SlotIndex) const
{
    for (const auto& Slot : Slots)
    {
        if (Slot.SlotIndex == SlotIndex)
        {
            return Slot;
        }
    }

    return FEquipmentSlot::EmptySlot;
}

bool UEquipmentManagerComponent::AddEquipmentToSlot(const TScriptInterface<IEquipmentActorInterface>& NewEquipment, const FEquipmentSlotIndex& SlotIndex)
{
    if (!NewEquipment) return false;
    if (!HasSlot(SlotIndex)) return false;

    FEquipmentSlot& Slot = GetSlotRef(SlotIndex);
    if (Slot.IsValid() && Slot.IsEmpty())
    {
        Slot.Equipment = NewEquipment;
        IEquipmentActorInterface::Execute_Equip(Slot.Equipment.GetObject(), GetOwner());
        // AttachActorToSocket(Slot.Socket, CastChecked<AActor>(NewEquipment.GetObject()));

        return true;
    }

    return false;
}

TScriptInterface<IEquipmentActorInterface> UEquipmentManagerComponent::RemoveEquipmentFromSlot(const FEquipmentSlotIndex& SlotIndex)
{
    if (!HasSlot(SlotIndex)) return nullptr;

    FEquipmentSlot& Slot = GetSlotRef(SlotIndex);
    if (Slot.IsValid() && !Slot.IsEmpty())
    {
        AActor* OldEquipmentActor = nullptr; //DetachActorFromSocket(Slot.Socket);
        IEquipmentActorInterface::Execute_UnEquip(Slot.Equipment.GetObject());
        Slot.Equipment = nullptr;

        return OldEquipmentActor;
    }

    return nullptr;
}

void UEquipmentManagerComponent::CreateSlots()
{
    Slots.Reset(SlotConfigs.Num());

    for (const auto& [EquipmentType, Sockets] : SlotConfigs)
    {
        if (SlotNumMap.Contains(EquipmentType)) continue;
        SlotNumMap.Emplace(EquipmentType, Sockets.Num());

        for (int32 Index = 0; Index < Sockets.Num(); ++Index)
        {
            FEquipmentSlot NewEquipmentSlot;
            NewEquipmentSlot.SlotIndex = FEquipmentSlotIndex(EquipmentType, Index);
            NewEquipmentSlot.Socket = Sockets[Index];

            Slots.Emplace(NewEquipmentSlot);
        }
    }
}

AActor* UEquipmentManagerComponent::SpawnActorByData(UDataAsset* Data)
{
    AActor* SpawnedActor = nullptr;

    if (Data && Data->Implements<UEquipmentDataInterface>())
    {
        TSubclassOf<AActor> ActorClass = IEquipmentDataInterface::Execute_GetActorClass(Data);
        if (ActorClass && ActorClass->ImplementsInterface(UEquipmentActorInterface::StaticClass()))
        {
            SpawnedActor = SpawnActorByClass(ActorClass);
            if (SpawnedActor)
            {
                IEquipmentActorInterface::Execute_SetEquipmentData(SpawnedActor, Data);
            }
        }
    }

    return SpawnedActor;
}

AActor* UEquipmentManagerComponent::SpawnActorByClass(TSubclassOf<AActor> ActorClass) const
{
    // 입력 유효성 검사
    if (ActorClass == nullptr) return nullptr;

    // 유효성 검사
    UWorld* World = GetWorld();
    AActor* Owner = GetOwner();
    if (World == nullptr || Owner == nullptr) return nullptr;

    // ActorSpawnParameters 설정
    FActorSpawnParameters ActorSpawnParameters;
    ActorSpawnParameters.Owner = Owner;
    ActorSpawnParameters.Instigator = Owner->GetInstigator();
    ActorSpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

    // 액터 스폰
    const FVector SpawnLocation = Owner->GetActorLocation();
    AActor* SpawnedActor = World->SpawnActor<AActor>(ActorClass, SpawnLocation, FRotator::ZeroRotator, ActorSpawnParameters);

    return SpawnedActor;
}
