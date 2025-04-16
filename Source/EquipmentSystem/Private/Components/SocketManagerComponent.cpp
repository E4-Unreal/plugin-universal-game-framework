// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/SocketManagerComponent.h"

#include "Actors/SocketMeshActor.h"
#include "Actors/SocketSkeletalMeshActor.h"
#include "Actors/SocketStaticMeshActor.h"
#include "GameFramework/Character.h"

USocketManagerComponent::USocketManagerComponent()
{
    bWantsInitializeComponent = true;

    OverrideBodyInstance.SetCollisionProfileName(UCollisionProfile::NoCollision_ProfileName);
}

void USocketManagerComponent::InitializeComponent()
{
    Super::InitializeComponent();

    SocketActorMap.Reserve(SocketNameMap.Num());

    if (auto OwnerCharacter = Cast<ACharacter>(GetOwner()))
    {
        SetTargetMesh(OwnerCharacter->GetMesh());
    }
}

void USocketManagerComponent::SetTargetMesh(USkeletalMeshComponent* Value)
{
    if (TargetMesh.IsValid()) return;

    TargetMesh = Value;
}

void USocketManagerComponent::AttachActorToSocket(const FGameplayTag& SocketTag, AActor* Actor)
{
    // 입력 유효성 검사
    if (Actor == nullptr || !DoesSocketExist(SocketTag)) return;

    // 액터 부착
    Actor->AttachToComponent(TargetMesh.Get(), FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true), GetSocketName(SocketTag));
    SocketActorMap.Emplace(SocketTag, Actor);
}

void USocketManagerComponent::SpawnActorToSocket(const FGameplayTag& SocketTag, TSubclassOf<AActor> ActorClass)
{
    // 입력 유효성 검사
    if (ActorClass == nullptr || !DoesSocketExist(SocketTag)) return;

    // 액터 스폰
    AActor* SpawnedActor = SpawnActor(ActorClass);
    if (SpawnedActor == nullptr) return;

    // 액터 부착
    AttachActorToSocket(SocketTag, SpawnedActor);
}

void USocketManagerComponent::SpawnSkeletalMeshToSocket(const FGameplayTag& SocketTag, USkeletalMesh* SkeletalMesh)
{
    SpawnMeshToSocket(SocketTag, SkeletalMesh);
}

void USocketManagerComponent::SpawnStaticMeshToSocket(const FGameplayTag& SocketTag, UStaticMesh* StaticMesh)
{
    SpawnMeshToSocket(SocketTag, StaticMesh);
}

AActor* USocketManagerComponent::SpawnActor(TSubclassOf<AActor> ActorClass)
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
    SpawnedActor->SetReplicates(GetIsReplicated());

    return SpawnedActor;
}

AActor* USocketManagerComponent::SpawnActorDeferred(TSubclassOf<AActor> ActorClass)
{
    // 입력 유효성 검사
    if (ActorClass == nullptr) return nullptr;

    // 유효성 검사
    UWorld* World = GetWorld();
    AActor* Owner = GetOwner();
    if (World == nullptr || Owner == nullptr) return nullptr;

    // 액터 스폰
    FTransform SpawnTransform = FTransform(Owner->GetActorLocation());
    AActor* SpawnedActor = World->SpawnActorDeferred<AActor>(ActorClass, SpawnTransform, Owner, Owner->GetInstigator(), ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn);
    SpawnedActor->SetReplicates(GetIsReplicated());

    return SpawnedActor;
}

void USocketManagerComponent::SpawnMeshToSocket(const FGameplayTag& SocketTag, UStreamableRenderAsset* Mesh)
{
    // 입력 유효성 검사
    if (Mesh == nullptr || !DoesSocketExist(SocketTag)) return;

    // 액터 스폰
    TSubclassOf<ASocketMeshActor> SocketMeshActorClass;
    if (Mesh->GetClass() == USkeletalMesh::StaticClass())
    {
        SocketMeshActorClass = ASocketSkeletalMeshActor::StaticClass();
    }
    else if (Mesh->GetClass() == UStaticMesh::StaticClass())
    {
        SocketMeshActorClass = ASocketStaticMeshActor::StaticClass();
    }
    else
    {
        return;
    }

    auto SpawnedActor = SpawnActor<ASocketMeshActor>(SocketMeshActorClass);
    SpawnedActor->SetBodyInstance(OverrideBodyInstance);
    SpawnedActor->SetMesh(Mesh);

    // 액터 부착
    AttachActorToSocket(SocketTag, SpawnedActor);
}

bool USocketManagerComponent::DoesSocketExist(const FGameplayTag& SocketTag) const
{
    FName SocketName = GetSocketName(SocketTag);
    if (SocketName.IsNone()) return false;

    return TargetMesh.IsValid() && TargetMesh->DoesSocketExist(SocketName);
}
