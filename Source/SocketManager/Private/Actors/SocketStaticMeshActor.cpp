// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/SocketStaticMeshActor.h"

ASocketStaticMeshActor::ASocketStaticMeshActor(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer.SetDefaultSubobjectClass(MeshComponentName, UStaticMeshComponent::StaticClass()))
{
    auto StaticMeshComponent = GetMeshComponent<UStaticMeshComponent>();
    StaticMeshComponent->SetMobility(EComponentMobility::Movable);
}

void ASocketStaticMeshActor::SetMesh(UStreamableRenderAsset* NewMesh)
{
    if (NewMesh == nullptr) return;

    Mesh = NewMesh;
    SetStaticMesh(Cast<UStaticMesh>(Mesh));
}

void ASocketStaticMeshActor::SetStaticMesh(UStaticMesh* NewMesh)
{
    auto StaticMeshComponent = GetMeshComponent<UStaticMeshComponent>();
    StaticMeshComponent->SetStaticMesh(NewMesh);
}
