// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/SocketManagerComponent.h"

#include "GameFramework/Character.h"


USocketManagerComponent::USocketManagerComponent()
{

}

void USocketManagerComponent::OnRegister()
{
    Super::OnRegister();

    FindRootMesh();
    InitializeSlots();
}

void USocketManagerComponent::SetRootMesh(UMeshComponent* NewRootMesh)
{
    RootMesh = NewRootMesh;
}

void USocketManagerComponent::ResetSlot(FGameplayTag InSocketTag)
{
    ClearSlot(InSocketTag);

    for (const auto& SlotConfig : SlotConfigs)
    {
        if (SlotConfig.SocketTag == InSocketTag)
        {
            ApplySlotConfig(SlotConfig);
            break;
        }
    }
}

void USocketManagerComponent::SetStaticMesh(UStaticMesh* NewStaticMesh, FGameplayTag SocketTag, FName SocketName)
{
    if (!RootMesh.IsValid() || !HasSlot(SocketTag)) return;

    if (NewStaticMesh && DoesSocketExist(SocketName))
    {
        ClearSlot(SocketTag);

        auto& Slot = const_cast<FSocketSlot&>(GetSlot(SocketTag));
        Slot.StaticMesh = GetOrCreateStaticMeshComponent();
        FAttachmentTransformRules AttachmentTransformRules(EAttachmentRule::SnapToTarget, true);
        Slot.StaticMesh->AttachToComponent(RootMesh.Get(), AttachmentTransformRules, SocketName);
        Slot.StaticMesh->SetStaticMesh(NewStaticMesh);
    }
    else
    {
        ResetSlot(SocketTag);
    }
}

void USocketManagerComponent::SetSkeletalMesh(USkeletalMesh* NewSkeletalMesh, FGameplayTag SocketTag, FName SocketName)
{
    if (!RootMesh.IsValid() || !HasSlot(SocketTag)) return;

    if (NewSkeletalMesh)
    {
        bool bModular = IsModular(NewSkeletalMesh);
        SocketName = bModular ? NAME_None: SocketName;

        if (!bModular && !DoesSocketExist(SocketName))
        {
            ResetSlot(SocketTag);
        }
        else
        {
            ClearSlot(SocketTag);

            auto& Slot = const_cast<FSocketSlot&>(GetSlot(SocketTag));
            Slot.SkeletalMesh = GetOrCreateSkeletalMeshComponent();
            FAttachmentTransformRules AttachmentTransformRules(EAttachmentRule::SnapToTarget, true);
            Slot.SkeletalMesh->AttachToComponent(RootMesh.Get(), AttachmentTransformRules, SocketName);
            Slot.SkeletalMesh->SetSkeletalMesh(NewSkeletalMesh);
        }
    }
    else
    {
        ResetSlot(SocketTag);
    }
}

AActor* USocketManagerComponent::SetActor(TSubclassOf<AActor> NewActorClass, FGameplayTag SocketTag, FName SocketName)
{
    AActor* Actor = nullptr;

    if (NewActorClass && HasSlot(SocketTag))
    {
        ClearSlot(SocketTag);

        auto& Slot = const_cast<FSocketSlot&>(GetSlot(SocketTag));

        if (RootMesh.IsValid())
        {
            Slot.Actor = SpawnActor(NewActorClass);
            Actor = Slot.Actor;

            if (DoesSocketExist(SocketName))
            {
                if (Slot.Actor->IsHidden()) Slot.Actor->SetHidden(false);
                FAttachmentTransformRules AttachmentTransformRules(EAttachmentRule::SnapToTarget, true);
                Slot.Actor->AttachToComponent(RootMesh.Get(), AttachmentTransformRules, SocketName);
            }
            else
            {
                if (!Slot.Actor->IsHidden()) Slot.Actor->SetHidden(true);
            }
        }
    }

    return Actor;
}

void USocketManagerComponent::FindRootMesh()
{
    if (RootMesh.IsValid()) return;

    UMeshComponent* FoundRootMesh = GetOwner()->IsA<ACharacter>()
        ? Cast<ACharacter>(GetOwner())->GetMesh()
        : GetOwner()->GetComponentByClass<UMeshComponent>();

    SetRootMesh(FoundRootMesh);
}

void USocketManagerComponent::InitializeSlots()
{
    // 슬롯 생성
    for (const auto& SlotConfig : SlotConfigs)
    {
        if (!SlotConfig.IsValid()) continue;

        FSocketSlot NewSlot;
        NewSlot.SocketTag = SlotConfig.SocketTag;

        Slots.Emplace(NewSlot);
    }

    // 슬롯 기본값 설정
    for (const auto& SlotConfig : SlotConfigs)
    {
        ApplySlotConfig(SlotConfig);
    }
}

bool USocketManagerComponent::HasSlot(FGameplayTag InSocketTag) const
{
    bool bResult = false;

    for (const auto& Slot : Slots)
    {
        if (Slot.SocketTag == InSocketTag)
        {
            bResult = true;
            break;
        }
    }

    return bResult;
}

const FSocketSlot& USocketManagerComponent::GetSlot(FGameplayTag InSocketTag)
{
    for (const auto& Slot : Slots)
    {
        if (Slot.SocketTag == InSocketTag)
        {
            return Slot;
        }
    }

    return FSocketSlot::EmptySlot;
}

void USocketManagerComponent::ClearSlot(FGameplayTag InSocketTag)
{
    if (HasSlot(InSocketTag))
    {
        auto& Slot = const_cast<FSocketSlot&>(GetSlot(InSocketTag));
        if (Slot.StaticMesh)
        {
            ReleaseStaticMeshComponent(Slot.StaticMesh);
            Slot.StaticMesh = nullptr;
        }
        else if (Slot.SkeletalMesh)
        {
            ReleaseSkeletalMeshComponent(Slot.SkeletalMesh);
            Slot.SkeletalMesh = nullptr;
        }
        else if (Slot.Actor)
        {
            Slot.Actor->Destroy();
            Slot.Actor = nullptr;
        }
    }
}

bool USocketManagerComponent::DoesSocketExist(FName InSocketName) const
{
    return RootMesh.IsValid() && RootMesh->DoesSocketExist(InSocketName);
}

bool USocketManagerComponent::IsModular(USkeletalMesh* InSkeletalMesh) const
{
    if (InSkeletalMesh)
    {
        if (auto RootSkeletalMeshComponent = Cast<USkeletalMeshComponent>(RootMesh.Get()))
        {
            if (auto RootSkeletalMesh = RootSkeletalMeshComponent->GetSkeletalMeshAsset())
            {
                if (RootSkeletalMesh->GetSkeleton()->IsCompatibleMesh(InSkeletalMesh))
                {
                    return true;
                }
            }
        }
    }

    return false;
}

UStaticMeshComponent* USocketManagerComponent::GetOrCreateStaticMeshComponent()
{
    UStaticMeshComponent* StaticMeshComponent = nullptr;

    if (StaticMeshComponentPool.IsEmpty())
    {
        if (RootMesh.IsValid())
        {
            StaticMeshComponent = NewObject<UStaticMeshComponent>(GetOwner());
            StaticMeshComponent->CreationMethod = EComponentCreationMethod::Instance;
            StaticMeshComponent->SetupAttachment(RootMesh.Get());
            StaticMeshComponent->SetCollisionProfileName(RootMesh->GetCollisionProfileName());
            StaticMeshComponent->RegisterComponent();
        }
    }
    else
    {
        StaticMeshComponent = StaticMeshComponentPool.Pop(EAllowShrinking::No);
        StaticMeshComponent->SetVisibility(true);
    }

    return StaticMeshComponent;
}

void USocketManagerComponent::ReleaseStaticMeshComponent(UStaticMeshComponent* StaticMeshComponent)
{
    if (StaticMeshComponent)
    {
        StaticMeshComponent->SetStaticMesh(nullptr);
        StaticMeshComponent->SetVisibility(false);
    }
}

USkeletalMeshComponent* USocketManagerComponent::GetOrCreateSkeletalMeshComponent()
{
    USkeletalMeshComponent* SkeletalMeshComponent = nullptr;

    if (StaticMeshComponentPool.IsEmpty())
    {
        if (RootMesh.IsValid())
        {
            SkeletalMeshComponent = NewObject<USkeletalMeshComponent>(GetOwner());
            SkeletalMeshComponent->CreationMethod = EComponentCreationMethod::Instance;
            SkeletalMeshComponent->SetupAttachment(RootMesh.Get());
            SkeletalMeshComponent->SetCollisionProfileName(RootMesh->GetCollisionProfileName());
            SkeletalMeshComponent->SetLeaderPoseComponent(Cast<USkeletalMeshComponent>(RootMesh));
            SkeletalMeshComponent->RegisterComponent();
        }
    }
    else
    {
        SkeletalMeshComponent = SkeletalMeshComponentPool.Pop(EAllowShrinking::No);
        SkeletalMeshComponent->SetVisibility(true);
    }

    return SkeletalMeshComponent;
}

void USocketManagerComponent::ReleaseSkeletalMeshComponent(USkeletalMeshComponent* SkeletalMeshComponent)
{
    if (SkeletalMeshComponent)
    {
        SkeletalMeshComponent->SetSkeletalMesh(nullptr);
        SkeletalMeshComponent->SetVisibility(false);
    }
}

AActor* USocketManagerComponent::SpawnActor(TSubclassOf<AActor> InActorClass)
{
    if (GetOwner()->HasAuthority() && InActorClass)
    {
        UWorld* World = GetWorld();
        AActor* Owner = GetOwner();

        // ActorSpawnParameters 설정
        FActorSpawnParameters ActorSpawnParameters;
        ActorSpawnParameters.Owner = Owner;
        ActorSpawnParameters.Instigator = Owner->GetInstigator();
        ActorSpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

        // 액터 스폰
        const FVector SpawnLocation = Owner->GetActorLocation();
        AActor* SpawnedActor = World->SpawnActor<AActor>(InActorClass, SpawnLocation, FRotator::ZeroRotator, ActorSpawnParameters);
        SpawnedActor->SetReplicates(true);

        return SpawnedActor;
    }

    return nullptr;
}

void USocketManagerComponent::ApplySlotConfig(const FSocketSlotConfig& InSlotConfig)
{
    if (InSlotConfig.IsValid())
    {
        auto SocketTag = InSlotConfig.SocketTag;
        auto SocketName = InSlotConfig.SocketName;
        auto DefaultStaticMesh = InSlotConfig.DefaultStaticMesh;
        auto DefaultSkeletalMesh = InSlotConfig.DefaultSkeletalMesh;
        auto DefaultActorClass = InSlotConfig.DefaultActorClass;

        if (DefaultActorClass)
        {
            SetActor(DefaultActorClass, SocketTag, SocketName);
        }
        else if (DefaultSkeletalMesh)
        {
            SetSkeletalMesh(DefaultSkeletalMesh, SocketTag, SocketName);
        }
        else if (DefaultStaticMesh)
        {
            SetStaticMesh(DefaultStaticMesh, SocketTag, SocketName);
        }
    }
}
