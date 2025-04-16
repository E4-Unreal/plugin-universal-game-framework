// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/SocketMeshActor.h"

#include "Net/UnrealNetwork.h"

const FName ASocketMeshActor::DefaultSceneRootName(TEXT("DefaultSceneRoot"));
const FName ASocketMeshActor::SkeletalMeshComponentName(TEXT("SkeletalMesh"));
const FName ASocketMeshActor::StaticMeshComponentName(TEXT("StaticMesh"));

ASocketMeshActor::ASocketMeshActor(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer)
{
    bReplicates = true;
    BodyInstance.SetCollisionProfileName(UCollisionProfile::NoCollision_ProfileName);

    /* DefaultSceneRoot */
    DefaultSceneRoot = CreateDefaultSubobject<USceneComponent>(DefaultSceneRootName);
    SetRootComponent(DefaultSceneRoot);

    /* SkeletalMeshComponent */
    SkeletalMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(SkeletalMeshComponentName);
    SkeletalMeshComponent->SetupAttachment(RootComponent);
    SkeletalMeshComponent->SetIsReplicated(true);

    /* StaticMeshComponent */
    StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(StaticMeshComponentName);
    StaticMeshComponent->SetupAttachment(RootComponent);
    StaticMeshComponent->SetIsReplicated(true);
    StaticMeshComponent->SetMobility(EComponentMobility::Movable);

    ApplyBodyInstance();
}

void ASocketMeshActor::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);

    DOREPLIFETIME(ThisClass, BodyInstance);
}

void ASocketMeshActor::SetSkeletalMesh(USkeletalMesh* SkeletalMesh)
{
    if (SkeletalMeshComponent) SkeletalMeshComponent->SetSkeletalMesh(SkeletalMesh);
}

void ASocketMeshActor::SetStaticMesh(UStaticMesh* StaticMesh)
{
    if (StaticMeshComponent) StaticMeshComponent->SetStaticMesh(StaticMesh);
}

void ASocketMeshActor::SetBodyInstance(const FBodyInstance& Value)
{
    BodyInstance = Value;
    ApplyBodyInstance();
}

void ASocketMeshActor::ApplyBodyInstance() const
{
    if (BodyInstance.GetCollisionProfileName() == UCollisionProfile::CustomCollisionProfileName)
    {
        SkeletalMeshComponent->SetCollisionEnabled(BodyInstance.GetCollisionEnabled());
        SkeletalMeshComponent->SetCollisionObjectType(BodyInstance.GetObjectType());
        SkeletalMeshComponent->SetCollisionResponseToChannels(BodyInstance.GetResponseToChannels());

        StaticMeshComponent->SetCollisionEnabled(BodyInstance.GetCollisionEnabled());
        StaticMeshComponent->SetCollisionObjectType(BodyInstance.GetObjectType());
        StaticMeshComponent->SetCollisionResponseToChannels(BodyInstance.GetResponseToChannels());
    }
    else
    {
        SkeletalMeshComponent->SetCollisionProfileName(BodyInstance.GetCollisionProfileName());

        StaticMeshComponent->SetCollisionProfileName(BodyInstance.GetCollisionProfileName());
    }
}

void ASocketMeshActor::OnRep_BodyInstance()
{
    ApplyBodyInstance();
}
