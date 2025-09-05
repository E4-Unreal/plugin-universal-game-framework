// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/WeaponManagerComponent.h"

#include "Data/WeaponInstance.h"
#include "GameplayTags/WeaponGameplayTags.h"
#include "Interfaces/WeaponActorInterface.h"
#include "Interfaces/WeaponDataInterface.h"
#include "Net/UnrealNetwork.h"

UWeaponManagerComponent::UWeaponManagerComponent()
{
    bWantsInitializeComponent = true;

    SlotConfig.Emplace(Weapon::Slot::Primary, 1);
    StartupSlotIndex = FWeaponSlotIndex(Weapon::Slot::Primary, 0);
}

void UWeaponManagerComponent::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);

    DOREPLIFETIME(ThisClass, Slots);
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

AActor* UWeaponManagerComponent::GetCurrentWeaponActor() const
{
    const auto& CurrentSlot = GetSlotByIndex(CurrentSlotIndex);

    return CurrentSlot.GetActor();
}

const FWeaponSlot& UWeaponManagerComponent::GetSlotByIndex(FWeaponSlotIndex InSlotIndex) const
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
        AttachWeaponActorToSocket(OldSlot.GetActor(), OldSlot.GetInActiveSocketName());
    }

    const FWeaponSlot& NewSlot = GetSlotByIndex(NewSlotIndex);
    if (!NewSlot.IsEmpty())
    {
        AttachWeaponActorToSocket(NewSlot.GetActor(), NewSlot.GetActiveSocketName());
    }
}

bool UWeaponManagerComponent::DoesSocketExist(FName SocketName) const
{
    return Mesh.IsValid() && Mesh->DoesSocketExist(SocketName);
}

bool UWeaponManagerComponent::DoesEmptySlotExist(FGameplayTag SlotType) const
{
    // TODO 리팩토링 캐싱 맵 방식으로 변경

    bool bResult = false;

    for (const auto& Slot : Slots)
    {
        if (Slot.Index.Type == SlotType && Slot.IsEmpty())
        {
            bResult = true;

            break;
        }
    }

    return bResult;
}

bool UWeaponManagerComponent::IsWeaponDataValid(const TScriptInterface<IWeaponDataInterface>& NewData) const
{
    if (NewData)
    {
        const FGameplayTag SlotType = IWeaponDataInterface::Execute_GetSlotType(NewData.GetObject());
        const TSubclassOf<AActor> WeaponActorClass = IWeaponDataInterface::Execute_GetWeaponActorClass(NewData.GetObject());
        const FName ActiveSocketName = IWeaponDataInterface::Execute_GetActiveSocketName(NewData.GetObject());

        return SlotConfig.Contains(SlotType) && WeaponActorClass && DoesSocketExist(ActiveSocketName);
    }

    return false;
}

bool UWeaponManagerComponent::CanAddWeaponByData(const TScriptInterface<IWeaponDataInterface>& NewData) const
{
    const FGameplayTag SlotType = IWeaponDataInterface::Execute_GetSlotType(NewData.GetObject());

    return IsWeaponDataValid(NewData) && DoesEmptySlotExist(SlotType);
}

bool UWeaponManagerComponent::AddWeaponByData(const TScriptInterface<IWeaponDataInterface>& NewWeaponData)
{
    if (CanAddWeaponByData(NewWeaponData))
    {
        ServerAddWeaponByData(NewWeaponData);

        return true;
    }

    return false;
}

void UWeaponManagerComponent::ServerAddWeaponByData_Implementation(
    const TScriptInterface<IWeaponDataInterface>& NewWeaponData)
{
    if (NewWeaponData)
    {
        const FGameplayTag SlotType = IWeaponDataInterface::Execute_GetSlotType(NewWeaponData.GetObject());
        const TSubclassOf<AActor> WeaponActorClass = IWeaponDataInterface::Execute_GetWeaponActorClass(NewWeaponData.GetObject());
        const FName ActiveSocketName = IWeaponDataInterface::Execute_GetActiveSocketName(NewWeaponData.GetObject());
        const FName InActiveSocketName = IWeaponDataInterface::Execute_GetActiveSocketName(NewWeaponData.GetObject());

        for (auto& Slot : Slots)
        {
            if (Slot.IsEmpty() && Slot.Index.Type == SlotType)
            {
                if (AActor* WeaponActor = SpawnWeaponActorByData(NewWeaponData))
                {
                    if (Slot == CurrentSlotIndex)
                    {
                        AttachWeaponActorToSocket(WeaponActor, ActiveSocketName);
                    }
                    else
                    {
                        AttachWeaponActorToSocket(WeaponActor, InActiveSocketName);
                    }

                    Slot.WeaponInstance = CreateReplicatedObject<UWeaponInstance>();
                    Slot.SetData(NewWeaponData);
                    Slot.SetActor(WeaponActor);

                    break;
                }
            }
        }
    }
}

void UWeaponManagerComponent::CreateSlots()
{
    if (!Slots.IsEmpty()) return;

    for (const auto& [SlotType, MaxNum] : SlotConfig)
    {
        for (int32 Index = 0; Index < MaxNum; ++Index)
        {
            FWeaponSlot NewSlot;
            NewSlot.Index = FWeaponSlotIndex(SlotType, Index);

            Slots.Emplace(NewSlot);
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

AActor* UWeaponManagerComponent::SpawnWeaponActorByData(const TScriptInterface<IWeaponDataInterface>& WeaponData) const
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
