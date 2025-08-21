// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/QuickSlotManagerComponent.h"

#include "Components/SocketManagerComponent.h"
#include "Interfaces/QuickSlotActorInterface.h"


UQuickSlotManagerComponent::UQuickSlotManagerComponent(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer)
{
    bWantsInitializeComponent = true;

    SlotNum = 4;
}

void UQuickSlotManagerComponent::InitializeComponent()
{
    Super::InitializeComponent();

    CreateSlots();
    FindSocketManager();
}

void UQuickSlotManagerComponent::SetSlotIndex(int32 NewSlotIndex)
{
    if (NewSlotIndex == SlotIndex || NewSlotIndex < 0 || NewSlotIndex >= SlotNum) return;

    int32 OldSlotIndex = SlotIndex;
    SlotIndex = NewSlotIndex;
    OnSlotIndexChanged(OldSlotIndex);
}

void UQuickSlotManagerComponent::SetSlotByData(int32 InSlotIndex,
    const TScriptInterface<IQuickSlotDataInterface>& NewData)
{
    FQuickSlot& Slot = const_cast<FQuickSlot&>(GetSlot(InSlotIndex));
    if (Slot.Data == NewData) return;

    if (Slot.IsValid())
    {
        SocketManager->DestroyActorFromSocket(Slot.GetSocketTag());
        Slot = FQuickSlot::EmptySlot;
    }

    Slot.Data = NewData;

    if (AActor* SpawnedActor = SocketManager->SpawnActorToSocket(Slot.GetSocketTag(), Slot.GetActorClass()))
    {
        Slot.Actor = SpawnedActor;
        if (Slot.Actor->Implements<UQuickSlotActorInterface>())
        {
            IQuickSlotActorInterface::Execute_SetQuickSlotData(SpawnedActor, Slot.Data);
        }

        if (InSlotIndex != SlotIndex)
        {
            SpawnedActor->SetActorHiddenInGame(false);
            SpawnedActor->SetActorEnableCollision(true);
        }
    }
}

void UQuickSlotManagerComponent::CreateSlots()
{
    Slots.Reserve(SlotNum);

    for (int32 Index = 0; Index < SlotNum; ++Index)
    {
        Slots.Emplace(FQuickSlot());
    }
}

void UQuickSlotManagerComponent::FindSocketManager()
{
    if (SocketManager.IsValid()) return;

    SocketManager = GetOwner()->FindComponentByClass<USocketManagerComponent>();
}

void UQuickSlotManagerComponent::OnSlotIndexChanged(int32 OldSlotIndex)
{
    const FQuickSlot& OldSlot = GetSlot(OldSlotIndex);
    if (OldSlot.IsValid())
    {
        OldSlot.Actor->SetActorHiddenInGame(true);
        OldSlot.Actor->SetActorEnableCollision(false);
    }

    const FQuickSlot& NewSlot = GetCurrentSlot();
    if (NewSlot.IsValid())
    {
        NewSlot.Actor->SetActorHiddenInGame(false);
        NewSlot.Actor->SetActorEnableCollision(true);
    }
}
