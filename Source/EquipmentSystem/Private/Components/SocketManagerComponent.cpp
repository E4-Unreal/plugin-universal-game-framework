// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/SocketManagerComponent.h"

#include "Actors/SocketMeshActor.h"
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
    // 입력 유효성 검사
    if (SkeletalMesh == nullptr || !DoesSocketExist(SocketTag)) return;

    // 액터 스폰
    auto SpawnedActor = SpawnActor<ASocketMeshActor>();
    SpawnedActor->SetBodyInstance(OverrideBodyInstance);
    SpawnedActor->SetSkeletalMesh(SkeletalMesh);

    // 액터 부착
    AttachActorToSocket(SocketTag, SpawnedActor);
}

void USocketManagerComponent::SpawnStaticMeshToSocket(const FGameplayTag& SocketTag, UStaticMesh* StaticMesh)
{
    // 입력 유효성 검사
    if (StaticMesh == nullptr || !DoesSocketExist(SocketTag)) return;

    // 액터 스폰
    auto SpawnedActor = SpawnActor<ASocketMeshActor>();
    SpawnedActor->SetBodyInstance(OverrideBodyInstance);
    SpawnedActor->SetStaticMesh(StaticMesh);

    // 액터 부착
    AttachActorToSocket(SocketTag, SpawnedActor);
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
    ActorSpawnParameters.Name = FName(Owner->GetName() + "_" + ActorClass->GetName());
    ActorSpawnParameters.Owner = Owner;
    ActorSpawnParameters.Instigator = Owner->GetInstigator();
    ActorSpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

    // 액터 스폰
    const FVector SpawnLocation = Owner->GetActorLocation();
    AActor* SpawnedActor = World->SpawnActor<AActor>(ActorClass, SpawnLocation, FRotator::ZeroRotator, ActorSpawnParameters);

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

    return SpawnedActor;
}

bool USocketManagerComponent::DoesSocketExist(const FGameplayTag& SocketTag) const
{
    FName SocketName = GetSocketName(SocketTag);
    if (SocketName.IsNone()) return false;

    return TargetMesh.IsValid() && TargetMesh->DoesSocketExist(SocketName);
}
