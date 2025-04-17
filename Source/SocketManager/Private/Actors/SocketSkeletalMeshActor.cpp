// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/SocketSkeletalMeshActor.h"

ASocketSkeletalMeshActor::ASocketSkeletalMeshActor(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer.SetDefaultSubobjectClass(MeshComponentName, USkeletalMeshComponent::StaticClass()))
{

}

void ASocketSkeletalMeshActor::SetMesh(UStreamableRenderAsset* NewMesh)
{
    if (Mesh == NewMesh) return;

    Mesh = NewMesh;
    SetSkeletalMesh(Cast<USkeletalMesh>(Mesh));
}

void ASocketSkeletalMeshActor::SetSkeletalMesh(USkeletalMesh* NewMesh, bool bReinitPose)
{
    auto SkeletalMeshComponent = GetMeshComponent<USkeletalMeshComponent>();
    SkeletalMeshComponent->SetSkeletalMesh(NewMesh, bReinitPose);
}
