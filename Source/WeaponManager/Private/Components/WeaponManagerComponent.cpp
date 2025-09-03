// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/WeaponManagerComponent.h"

#include "Interfaces/WeaponActorInterface.h"
#include "Interfaces/WeaponDataInterface.h"

UWeaponManagerComponent::UWeaponManagerComponent()
{
    bWantsInitializeComponent = true;
}

void UWeaponManagerComponent::InitializeComponent()
{
    Super::InitializeComponent();

    CreateSlots();
}

bool UWeaponManagerComponent::AddWeaponByData(const TScriptInterface<IWeaponDataInterface>& NewWeaponData)
{
    bool bResult = false;

    if (NewWeaponData)
    {
        const FGameplayTag SlotType = IWeaponDataInterface::Execute_GetSlotType(NewWeaponData.GetObject());
        const TSubclassOf<AActor> WeaponActorClass = IWeaponDataInterface::Execute_GetWeaponActorClass(NewWeaponData.GetObject());
        const FName ActiveSocketName = IWeaponDataInterface::Execute_GetActiveSocketName(NewWeaponData.GetObject());
        const FName InActiveSocketName = IWeaponDataInterface::Execute_GetActiveSocketName(NewWeaponData.GetObject());

        for (auto& Slot : Slots)
        {
            if (Slot.IsEmpty() && Slot.Type == SlotType)
            {
                if (AActor* WeaponActor = SpawnWeaponActor(WeaponActorClass))
                {
                    if (Slot == CurrentSlotIndex)
                    {
                        AttachWeaponActorToSocket(WeaponActor, ActiveSocketName);
                    }
                    else
                    {
                        AttachWeaponActorToSocket(WeaponActor, InActiveSocketName);
                    }

                    Slot.Data = NewWeaponData;
                    Slot.Actor = WeaponActor;
                    bResult = true;

                    break;
                }
            }
        }
    }

    return bResult;
}

void UWeaponManagerComponent::CreateSlots()
{
    if (!Slots.IsEmpty()) return;

    for (const auto& [SlotType, MaxNum] : SlotConfig)
    {
        for (int32 Index = 0; Index < MaxNum; ++Index)
        {
            Slots.Emplace(FWeaponSlot(SlotType, Index));
        }
    }
}

AActor* UWeaponManagerComponent::SpawnWeaponActor(TSubclassOf<AActor> WeaponActorClass) const
{
    AActor* WeaponActor = nullptr;

    if (WeaponActorClass && WeaponActorClass->ImplementsInterface(UWeaponActorInterface::StaticClass()))
    {
        FActorSpawnParameters ActorSpawnParameters;
        ActorSpawnParameters.Owner = GetOwner();
        ActorSpawnParameters.Instigator = GetOwner()->GetInstigator();
        ActorSpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

        const FVector SpawnLocation = GetOwner()->GetActorLocation();
        WeaponActor = GetWorld()->SpawnActor<AActor>(WeaponActorClass, SpawnLocation, FRotator::ZeroRotator, ActorSpawnParameters);
    }

    return WeaponActor;
}

bool UWeaponManagerComponent::AttachWeaponActorToSocket(AActor* WeaponActor, const FName SocketName) const
{
    bool bResult = false;

    if (WeaponActor && Mesh.IsValid() && Mesh->DoesSocketExist(SocketName))
    {
        FAttachmentTransformRules AttachmentTransformRules = FAttachmentTransformRules(
            EAttachmentRule::SnapToTarget,
            EAttachmentRule::SnapToTarget,
            EAttachmentRule::KeepWorld,
            true);

        bResult = WeaponActor->AttachToComponent(Mesh.Get(), AttachmentTransformRules, SocketName);
        WeaponActor->SetActorHiddenInGame(!bResult);
    }

    return bResult;
}
