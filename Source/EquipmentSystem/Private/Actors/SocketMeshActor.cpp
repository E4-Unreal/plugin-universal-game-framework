// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/SocketMeshActor.h"

const FName ASocketMeshActor::DefaultSceneRootName(TEXT("DefaultSceneRoot"));
const FName ASocketMeshActor::SkeletalMeshComponentName(TEXT("SkeletalMesh"));
const FName ASocketMeshActor::StaticMeshComponentName(TEXT("StaticMesh"));

ASocketMeshActor::ASocketMeshActor(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer)
{
    bReplicates = true;

    /* DefaultSceneRoot */
    DefaultSceneRoot = CreateDefaultSubobject<USceneComponent>(DefaultSceneRootName);
    SetRootComponent(DefaultSceneRoot);

    /* SkeletalMeshComponent */
    SkeletalMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(SkeletalMeshComponentName);
    SkeletalMeshComponent->SetupAttachment(RootComponent);
    SkeletalMeshComponent->SetIsReplicated(true);
    SkeletalMeshComponent->SetCollisionProfileName(UCollisionProfile::NoCollision_ProfileName);

    /* StaticMeshComponent */
    StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(StaticMeshComponentName);
    StaticMeshComponent->SetupAttachment(RootComponent);
    StaticMeshComponent->SetIsReplicated(true);
    StaticMeshComponent->SetMobility(EComponentMobility::Movable);
    StaticMeshComponent->SetCollisionProfileName(UCollisionProfile::NoCollision_ProfileName);
}

void ASocketMeshActor::SetSkeletalMesh(USkeletalMesh* SkeletalMesh)
{
    if (SkeletalMeshComponent) SkeletalMeshComponent->SetSkeletalMesh(SkeletalMesh);
}

void ASocketMeshActor::SetStaticMesh(UStaticMesh* StaticMesh)
{
    if (StaticMeshComponent) StaticMeshComponent->SetStaticMesh(StaticMesh);
}

void ASocketMeshActor::SetBodyInstance(const FBodyInstance& OverrideBodyInstance)
{
    FName OverrideCollisionProfileName = OverrideBodyInstance.GetCollisionProfileName();
    if (OverrideCollisionProfileName != UCollisionProfile::CustomCollisionProfileName && OverrideCollisionProfileName == SkeletalMeshComponent->GetCollisionProfileName()) return;

    NetMulticast_SetBodyInstance(OverrideBodyInstance);
}

void ASocketMeshActor::NetMulticast_SetBodyInstance_Implementation(const FBodyInstance& OverrideBodyInstance)
{
    InternalSetBodyInstance(OverrideBodyInstance);
}

void ASocketMeshActor::InternalSetBodyInstance(const FBodyInstance& OverrideBodyInstance)
{
    if (OverrideBodyInstance.GetCollisionProfileName() == UCollisionProfile::CustomCollisionProfileName)
    {
        SkeletalMeshComponent->SetCollisionEnabled(OverrideBodyInstance.GetCollisionEnabled());
        SkeletalMeshComponent->SetCollisionObjectType(OverrideBodyInstance.GetObjectType());
        SkeletalMeshComponent->SetCollisionResponseToChannels(OverrideBodyInstance.GetResponseToChannels());

        StaticMeshComponent->SetCollisionEnabled(OverrideBodyInstance.GetCollisionEnabled());
        StaticMeshComponent->SetCollisionObjectType(OverrideBodyInstance.GetObjectType());
        StaticMeshComponent->SetCollisionResponseToChannels(OverrideBodyInstance.GetResponseToChannels());
    }
    else
    {
        SkeletalMeshComponent->SetCollisionProfileName(OverrideBodyInstance.GetCollisionProfileName());

        StaticMeshComponent->SetCollisionProfileName(OverrideBodyInstance.GetCollisionProfileName());
    }
}
