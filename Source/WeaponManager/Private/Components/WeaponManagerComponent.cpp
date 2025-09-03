// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/WeaponManagerComponent.h"

#include "GameplayTags/WeaponGameplayTags.h"
#include "Interfaces/WeaponActorInterface.h"
#include "Interfaces/WeaponDataInterface.h"

UWeaponManagerComponent::UWeaponManagerComponent()
{
    bWantsInitializeComponent = true;

    SlotConfig.Emplace(Weapon::Slot::Primary, 1);
    StartupSlotIndex = FWeaponSlotIndex(Weapon::Slot::Primary, 0);
}

void UWeaponManagerComponent::InitializeComponent()
{
    Super::InitializeComponent();

    FindMesh();
    CreateSlots();
}

void UWeaponManagerComponent::BeginPlay()
{
    Super::BeginPlay();

    SetSlotIndex(StartupSlotIndex);
}

const FWeaponSlot& UWeaponManagerComponent::GetSlotByIndex(FWeaponSlotIndex InSlotIndex)
{
    for (const auto& Slot : Slots)
    {
        if (Slot == InSlotIndex)
        {
            return Slot;
        }
    }

    return FWeaponSlot::EmptySlot;
}

void UWeaponManagerComponent::SetSlotIndex(FWeaponSlotIndex NewSlotIndex, bool bForce)
{
    if (!bForce && CurrentSlotIndex == NewSlotIndex) return;

    FWeaponSlotIndex OldSlotIndex = CurrentSlotIndex;
    CurrentSlotIndex = NewSlotIndex;

    const FWeaponSlot& OldSlot = GetSlotByIndex(OldSlotIndex);
    if (!OldSlot.IsEmpty())
    {
        AttachWeaponActorToSocket(OldSlot.Actor, OldSlot.GetInActiveSocketName());
    }

    const FWeaponSlot& NewSlot = GetSlotByIndex(NewSlotIndex);
    if (!NewSlot.IsEmpty())
    {
        AttachWeaponActorToSocket(NewSlot.Actor, NewSlot.GetActiveSocketName());
    }
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

void UWeaponManagerComponent::FindMesh()
{
    if (!Mesh.IsValid())
    {
        Mesh = GetOwner()->GetComponentByClass<USkeletalMeshComponent>();
    }
}

AActor* UWeaponManagerComponent::SpawnWeaponActor(const TScriptInterface<IWeaponDataInterface>& WeaponData) const
{
    AActor* WeaponActor = nullptr;

    if (WeaponData)
    {
        if (TSubclassOf<AActor> WeaponActorClass = IWeaponDataInterface::Execute_GetWeaponActorClass(WeaponData.GetObject()))
        {
            FActorSpawnParameters ActorSpawnParameters;
            ActorSpawnParameters.Owner = GetOwner();
            ActorSpawnParameters.Instigator = GetOwner()->GetInstigator();
            ActorSpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

            const FVector SpawnLocation = GetOwner()->GetActorLocation();
            WeaponActor = GetWorld()->SpawnActor<AActor>(WeaponActorClass, SpawnLocation, FRotator::ZeroRotator, ActorSpawnParameters);

            if (WeaponActor && WeaponActor->Implements<UWeaponActorInterface>())
            {
                IWeaponActorInterface::Execute_SetWeaponData(WeaponActor, WeaponData);
            }
        }
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
