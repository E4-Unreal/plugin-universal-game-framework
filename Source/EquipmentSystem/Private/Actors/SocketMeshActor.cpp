// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/SocketMeshActor.h"

#include "Net/UnrealNetwork.h"
#include "Logging.h"

const FName ASocketMeshActor::MeshComponentName(TEXT("Mesh"));

ASocketMeshActor::ASocketMeshActor(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer)
{
    /* MeshComponent */
    MeshComponent = CreateDefaultSubobject<UMeshComponent>(MeshComponentName);
    SetRootComponent(MeshComponent);
    if (MeshComponent)
    {
        MeshComponent->SetCollisionProfileName(UCollisionProfile::NoCollision_ProfileName);
        BodyInstance = MeshComponent->BodyInstance;
    }
}

void ASocketMeshActor::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);

    DOREPLIFETIME(ThisClass, Mesh);
    DOREPLIFETIME(ThisClass, BodyInstance);
}

void ASocketMeshActor::SetMesh(UStreamableRenderAsset* NewMesh)
{
    if (Mesh == NewMesh) return;

    Mesh = NewMesh;
}

void ASocketMeshActor::SetBodyInstance(const FBodyInstance& NewBodyInstance)
{
    // 중복 호출 방지
    FName OldCollisionProfileName = BodyInstance.GetCollisionProfileName();
    if (OldCollisionProfileName != UCollisionProfile::CustomCollisionProfileName && OldCollisionProfileName == NewBodyInstance.GetCollisionProfileName()) return;

    // BodyInstance 설정
    BodyInstance = NewBodyInstance;
    ApplyBodyInstance();
}

void ASocketMeshActor::ApplyBodyInstance() const
{
    if (BodyInstance.GetCollisionProfileName() == UCollisionProfile::CustomCollisionProfileName)
    {
        MeshComponent->SetCollisionEnabled(BodyInstance.GetCollisionEnabled());
        MeshComponent->SetCollisionObjectType(BodyInstance.GetObjectType());
        MeshComponent->SetCollisionResponseToChannels(BodyInstance.GetResponseToChannels());
    }
    else
    {
        MeshComponent->SetCollisionProfileName(BodyInstance.GetCollisionProfileName());
    }
}

void ASocketMeshActor::OnRep_Mesh(UStreamableRenderAsset* OldMesh)
{
    auto NewMesh = Mesh;
    if (OldMesh == NewMesh) return;

    Mesh = OldMesh;
    SetMesh(NewMesh);
}

void ASocketMeshActor::OnRep_BodyInstance()
{
    ApplyBodyInstance();
}
