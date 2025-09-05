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

    return CurrentSlot.Actor.Get();
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
        AttachWeaponActorToSocket(OldSlot.Actor.Get(), OldSlot.GetInActiveSocketName());
    }

    const FWeaponSlot& NewSlot = GetSlotByIndex(NewSlotIndex);
    if (!NewSlot.IsEmpty())
    {
        AttachWeaponActorToSocket(NewSlot.Actor.Get(), NewSlot.GetActiveSocketName());
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

bool UWeaponManagerComponent::CanAddWeaponFromData(TSoftObjectPtr<UDataAsset> NewData) const
{
    if (CheckData(NewData))
    {
        UDataAsset* LoadedData = NewData.LoadSynchronous();
        const FGameplayTag SlotType = IWeaponDataInterface::Execute_GetSlotType(LoadedData);

        return DoesEmptySlotExist(SlotType);
    }

    return false;
}

void UWeaponManagerComponent::AddWeaponFromData(TSoftObjectPtr<UDataAsset> NewData)
{
    if (CanAddWeaponFromData(NewData))
    {
        UDataAsset* LoadedData = NewData.LoadSynchronous();
        const FGameplayTag SlotType = IWeaponDataInterface::Execute_GetSlotType(LoadedData);
        const FName ActiveSocketName = IWeaponDataInterface::Execute_GetActiveSocketName(LoadedData);
        const FName InActiveSocketName = IWeaponDataInterface::Execute_GetActiveSocketName(LoadedData);

        for (auto& Slot : Slots)
        {
            if (Slot.IsEmpty() && Slot.Index.Type == SlotType)
            {
                if (AActor* Actor = SpawnActorFromData(NewData))
                {
                    if (Slot == CurrentSlotIndex)
                    {
                        AttachWeaponActorToSocket(Actor, ActiveSocketName);
                    }
                    else
                    {
                        AttachWeaponActorToSocket(Actor, InActiveSocketName);
                    }

                    Slot.Actor = Actor;

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

AActor* UWeaponManagerComponent::SpawnActorFromInstance(UReplicatedObject* Instance)
{
    if (CheckInstance(Instance))
    {
        UDataAsset* Data = IWeaponInstanceInterface::Execute_GetData(Instance).LoadSynchronous();
        TSubclassOf<AActor> ActorClass = IWeaponDataInterface::Execute_GetActorClass(Data);

        FActorSpawnParameters ActorSpawnParameters;
        ActorSpawnParameters.Owner = GetOwner();
        ActorSpawnParameters.Instigator = GetOwner()->GetInstigator();
        ActorSpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

        const FVector SpawnLocation = GetOwner()->GetActorLocation();
        if (AActor* SpawnedActor = GetWorld()->SpawnActor<AActor>(ActorClass, SpawnLocation, FRotator::ZeroRotator, ActorSpawnParameters))
        {
            IWeaponActorInterface::Execute_SetInstance(SpawnedActor, Instance);

            if (CheckActor(SpawnedActor))
            {
                return SpawnedActor;
            }
            else
            {
                SpawnedActor->Destroy();
            }
        }
    }

    return nullptr;
}

UReplicatedObject* UWeaponManagerComponent::CreateInstance(TSoftObjectPtr<UDataAsset> Data)
{
    if (CheckData(Data))
    {
        UDataAsset* LoadedData = Data.LoadSynchronous();
        TSubclassOf<UReplicatedObject> InstanceClass = IWeaponDataInterface::Execute_GetInstanceClass(LoadedData);
        if (CheckInstanceClass(InstanceClass))
        {
            if (UReplicatedObject* Instance = CreateReplicatedObject(InstanceClass))
            {
                IWeaponInstanceInterface::Execute_SetData(Instance, LoadedData);

                return Instance;
            }
        }
    }

    return nullptr;
}

bool UWeaponManagerComponent::CheckActor(AActor* Actor)
{
    if (Actor && Actor->Implements<UWeaponActorInterface>())
    {
        return CheckInstance(IWeaponActorInterface::Execute_GetInstance(Actor));
    }

    return false;
}

bool UWeaponManagerComponent::CheckActorClass(TSubclassOf<AActor> ActorClass)
{
    return ActorClass && ActorClass->ImplementsInterface(UWeaponActorInterface::StaticClass());
}

bool UWeaponManagerComponent::CheckInstance(UReplicatedObject* Instance)
{
    if (Instance && Instance->Implements<UWeaponInstanceInterface>())
    {
        return CheckData(IWeaponInstanceInterface::Execute_GetData(Instance));
    }

    return false;
}

bool UWeaponManagerComponent::CheckInstanceClass(TSubclassOf<UReplicatedObject> InstanceClass)
{
    return InstanceClass && InstanceClass->ImplementsInterface(UWeaponInstanceInterface::StaticClass());
}

bool UWeaponManagerComponent::CheckData(TSoftObjectPtr<UDataAsset> Data) const
{
    if (!Data.IsNull() && Data->Implements<UWeaponDataInterface>())
    {
        UDataAsset* LoadedData = Data.LoadSynchronous();
        const FGameplayTag SlotType = IWeaponDataInterface::Execute_GetSlotType(LoadedData);
        const TSubclassOf<AActor> WeaponActorClass = IWeaponDataInterface::Execute_GetActorClass(LoadedData);
        const FName ActiveSocketName = IWeaponDataInterface::Execute_GetActiveSocketName(LoadedData);

        return SlotConfig.Contains(SlotType) && WeaponActorClass && DoesSocketExist(ActiveSocketName);
    }

    return false;
}
