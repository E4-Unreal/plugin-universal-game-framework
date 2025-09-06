// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/WeaponManagerComponent.h"

#include "Data/WeaponInstance.h"
#include "GameplayTags/WeaponGameplayTags.h"
#include "Interfaces/WeaponActorInterface.h"
#include "Interfaces/WeaponDataInterface.h"
#include "Objects/SlotContent.h"

UWeaponManagerComponent::UWeaponManagerComponent()
{
    bWantsInitializeComponent = true;

    SlotConfig.Emplace(Weapon::Slot::Primary, 1);
}

void UWeaponManagerComponent::InitializeComponent()
{
    Super::InitializeComponent();

    FindMesh();
}

AActor* UWeaponManagerComponent::GetCurrentWeaponActor() const
{
    USlotContent* CurrentContent = GetContent(CurrentIndex);
    if (CheckInstance(CurrentContent))
    {
        AActor* Actor = IWeaponInstanceInterface::Execute_GetActor(CurrentContent);

        return Actor;
    }

    return nullptr;
}

void UWeaponManagerComponent::SetSlotIndex_Implementation(FWeaponSlotIndex NewSlotIndex, bool bForce)
{
    int32 NewIndex = GetIndex(NewSlotIndex);
    if (!SlotMap.Contains(NewIndex)) return;
    if (!bForce && CurrentIndex == NewIndex) return;

    int32 OldIndex = CurrentIndex;
    CurrentIndex = NewIndex;

    USlotContent* OldContent = GetContent(OldIndex);
    if (CheckInstance(OldContent))
    {
        AActor* Actor = IWeaponInstanceInterface::Execute_GetActor(OldContent);
        TSoftObjectPtr<UDataAsset> Data = IWeaponInstanceInterface::Execute_GetData(OldContent);
        const FName InActiveSocketName = IWeaponDataInterface::Execute_GetInActiveSocketName(Data.LoadSynchronous());

        AttachWeaponActorToSocket(Actor, InActiveSocketName);
    }

    USlotContent* NewContent = GetContent(NewIndex);
    if (CheckInstance(NewContent))
    {
        AActor* Actor = IWeaponInstanceInterface::Execute_GetActor(NewContent);
        TSoftObjectPtr<UDataAsset> Data = IWeaponInstanceInterface::Execute_GetData(NewContent);
        const FName ActiveSocketName = IWeaponDataInterface::Execute_GetActiveSocketName(Data.LoadSynchronous());

        AttachWeaponActorToSocket(Actor, ActiveSocketName);
    }
}

bool UWeaponManagerComponent::DoesSocketExist(FName SocketName) const
{
    return Mesh.IsValid() && Mesh->DoesSocketExist(SocketName);
}

bool UWeaponManagerComponent::DoesEmptySlotExist(FGameplayTag SlotType) const
{
    for (const auto& [SlotIndex, Index] : SlotIndexMap)
    {
        if (SlotIndex.Type == SlotType && IsEmpty(Index))
        {
            return true;
        }
    }

    return false;
}

bool UWeaponManagerComponent::CanAddWeaponFromData(const TSoftObjectPtr<UDataAsset>& NewData) const
{
    if (CheckData(NewData))
    {
        UDataAsset* LoadedData = NewData.LoadSynchronous();
        const FGameplayTag SlotType = IWeaponDataInterface::Execute_GetSlotType(LoadedData);

        return DoesEmptySlotExist(SlotType);
    }

    return false;
}

void UWeaponManagerComponent::AddWeaponFromData(const TSoftObjectPtr<UDataAsset>& NewData)
{
    if (CanAddWeaponFromData(NewData))
    {
        UDataAsset* LoadedData = NewData.LoadSynchronous();
        const FGameplayTag SlotType = IWeaponDataInterface::Execute_GetSlotType(LoadedData);
        const FName ActiveSocketName = IWeaponDataInterface::Execute_GetActiveSocketName(LoadedData);
        const FName InActiveSocketName = IWeaponDataInterface::Execute_GetActiveSocketName(LoadedData);

        for (auto& [SlotIndex, Index] : SlotIndexMap)
        {
            if (IsEmpty(Index) && SlotIndex.Type == SlotType)
            {
                if (AActor* Actor = SpawnActorFromData(NewData))
                {
                    if (Index == CurrentIndex)
                    {
                        AttachWeaponActorToSocket(Actor, ActiveSocketName);
                    }
                    else
                    {
                        AttachWeaponActorToSocket(Actor, InActiveSocketName);
                    }

                    USlotContent* NewContent = IWeaponActorInterface::Execute_GetInstance(Actor);
                    SetContent(Index, NewContent);

                    break;
                }
            }
        }
    }
}

void UWeaponManagerComponent::CreateSlots()
{
    int32 SlotIndex = -1;
    for (const auto& [SlotType, MaxNum] : SlotConfig)
    {
        for (int32 Index = 0; Index < MaxNum; ++Index)
        {
            ++SlotIndex;

            SlotIndexMap.Emplace(FWeaponSlotIndex(SlotType, Index), SlotIndex);
            Slots.Emplace(SlotIndex, nullptr);
        }
    }

    MaxSlotNum = SlotIndex + 1;
}

int32 UWeaponManagerComponent::GetIndex(const FWeaponSlotIndex& SlotIndex)
{
    return SlotIndexMap.Contains(SlotIndex) ? SlotIndexMap[SlotIndex] : -1;
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

AActor* UWeaponManagerComponent::SpawnActorFromInstance(USlotContent* Instance)
{
    if (CheckInstance(Instance))
    {
        UDataAsset* Data = IWeaponInstanceInterface::Execute_GetData(Instance);
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
                IWeaponInstanceInterface::Execute_SetActor(Instance, SpawnedActor);
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

USlotContent* UWeaponManagerComponent::CreateInstance(const TSoftObjectPtr<UDataAsset>& Data)
{
    if (CheckData(Data))
    {
        UDataAsset* LoadedData = Data.LoadSynchronous();
        TSubclassOf<USlotContent> InstanceClass = IWeaponDataInterface::Execute_GetInstanceClass(LoadedData);
        if (CheckInstanceClass(InstanceClass))
        {
            if (USlotContent* Instance = CreateReplicatedObject<USlotContent>(InstanceClass))
            {
                IWeaponInstanceInterface::Execute_SetData(Instance, LoadedData);

                return Instance;
            }
        }
    }

    return nullptr;
}

bool UWeaponManagerComponent::CheckActor(AActor* Actor) const
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

bool UWeaponManagerComponent::CheckInstance(USlotContent* Instance) const
{
    if (Instance && Instance->Implements<UWeaponInstanceInterface>())
    {
        return CheckData(IWeaponInstanceInterface::Execute_GetData(Instance));
    }

    return false;
}

bool UWeaponManagerComponent::CheckInstanceClass(TSubclassOf<USlotContent> InstanceClass)
{
    return InstanceClass && InstanceClass->ImplementsInterface(UWeaponInstanceInterface::StaticClass());
}

bool UWeaponManagerComponent::CheckData(const TSoftObjectPtr<UDataAsset>& Data) const
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
