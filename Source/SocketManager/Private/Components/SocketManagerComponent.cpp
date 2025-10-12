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

void USocketManagerComponent::SetStaticMesh(UStaticMesh* NewStaticMesh, FGameplayTag SocketTag, FName SocketName)
{
    if (NewStaticMesh && HasSlot(SocketTag))
    {
        ClearSlot(SocketTag);

        auto& Slot = const_cast<FSocketSlot&>(GetSlot(SocketTag));

        if (RootMesh.IsValid())
        {
            // StaticMeshComponent 생성
            if (Slot.StaticMesh == nullptr) Slot.StaticMesh = CreateStaticMesh();

            // StaticMesh 설정
            Slot.StaticMesh->SetStaticMesh(NewStaticMesh);

            // StaticMeshComponent를 소켓에 부착
            if (DoesSocketExist(SocketName))
            {
                if (!Slot.StaticMesh->IsVisible()) Slot.StaticMesh->SetVisibility(true);
                FAttachmentTransformRules AttachmentTransformRules(EAttachmentRule::SnapToTarget, true);
                Slot.StaticMesh->AttachToComponent(RootMesh.Get(), AttachmentTransformRules, SocketName);
            }
            else
            {
                if (Slot.StaticMesh->IsVisible()) Slot.StaticMesh->SetVisibility(false);
            }
        }
    }
}

void USocketManagerComponent::SetSkeletalMesh(USkeletalMesh* NewSkeletalMesh, FGameplayTag SocketTag, bool bModular,
    FName SocketName)
{
    if (NewSkeletalMesh && HasSlot(SocketTag))
    {
        ClearSlot(SocketTag);

        auto& Slot = const_cast<FSocketSlot&>(GetSlot(SocketTag));

        if (RootMesh.IsValid())
        {
            // SkeletalMeshComponent 생성
            if (Slot.SkeletalMesh == nullptr) Slot.SkeletalMesh = CreateSkeletalMesh();

            // SkeletalMesh 설정
            Slot.SkeletalMesh->SetSkeletalMesh(NewSkeletalMesh);

            if (bModular)
            {
                if (!Slot.SkeletalMesh->IsVisible()) Slot.SkeletalMesh->SetVisibility(true);
                FAttachmentTransformRules AttachmentTransformRules(EAttachmentRule::SnapToTarget, true);
                Slot.SkeletalMesh->AttachToComponent(RootMesh.Get(), AttachmentTransformRules);
            }
            else if (DoesSocketExist(SocketName))
            {
                if (!Slot.SkeletalMesh->IsVisible()) Slot.SkeletalMesh->SetVisibility(true);
                FAttachmentTransformRules AttachmentTransformRules(EAttachmentRule::SnapToTarget, true);
                Slot.SkeletalMesh->AttachToComponent(RootMesh.Get(), AttachmentTransformRules, SocketName);
            }
            else
            {
                if (Slot.SkeletalMesh->IsVisible()) Slot.SkeletalMesh->SetVisibility(false);
            }
        }
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
        // 슬롯 비우기
        auto& Slot = const_cast<FSocketSlot&>(GetSlot(InSocketTag));
        if (Slot.StaticMesh) Slot.StaticMesh->SetStaticMesh(nullptr);
        if (Slot.SkeletalMesh) Slot.SkeletalMesh->SetSkeletalMesh(nullptr);
        if (Slot.Actor) Slot.Actor->Destroy(); Slot.Actor = nullptr;

        // 기본값 적용
        for (const auto& SlotConfig : SlotConfigs)
        {
            if (SlotConfig.SocketTag == InSocketTag)
            {
                ApplySlotConfig(SlotConfig);
                break;
            }
        }
    }
}

bool USocketManagerComponent::DoesSocketExist(FName InSocketName) const
{
    return RootMesh.IsValid() && RootMesh->DoesSocketExist(InSocketName);
}

UStaticMeshComponent* USocketManagerComponent::CreateStaticMesh()
{
    if (RootMesh.IsValid())
    {
        auto NewStaticMesh = Cast<UStaticMeshComponent>(GetOwner()->AddComponentByClass(UStaticMeshComponent::StaticClass(), true, FTransform::Identity, false));
        NewStaticMesh->SetCollisionProfileName(RootMesh->GetCollisionProfileName());
        return NewStaticMesh;
    }

    return nullptr;
}

USkeletalMeshComponent* USocketManagerComponent::CreateSkeletalMesh()
{
    if (RootMesh.IsValid())
    {
        auto NewSkeletalMesh = Cast<USkeletalMeshComponent>(GetOwner()->AddComponentByClass(USkeletalMeshComponent::StaticClass(), true, FTransform::Identity, false));
        NewSkeletalMesh->SetCollisionProfileName(RootMesh->GetCollisionProfileName());
        NewSkeletalMesh->SetLeaderPoseComponent(Cast<USkinnedMeshComponent>(RootMesh.Get()));

        return NewSkeletalMesh;
    }

    return nullptr;
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
        auto bModular = InSlotConfig.bModular;
        auto DefaultActorClass = InSlotConfig.DefaultActorClass;

        if (DefaultActorClass)
        {
            SetActor(DefaultActorClass, SocketTag, SocketName);
        }
        else if (DefaultSkeletalMesh)
        {
            SetSkeletalMesh(DefaultSkeletalMesh, SocketTag, bModular, SocketName);
        }
        else if (DefaultStaticMesh)
        {
            SetStaticMesh(DefaultStaticMesh, SocketTag, SocketName);
        }
    }
}
