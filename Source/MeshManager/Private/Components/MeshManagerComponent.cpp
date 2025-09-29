// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/MeshManagerComponent.h"

#include "GameFramework/Character.h"
#include "Interfaces/MeshDataInterface.h"


UMeshManagerComponent::UMeshManagerComponent()
{
    bWantsInitializeComponent = true;
}

#if WITH_EDITOR
void UMeshManagerComponent::PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent)
{
    if (PropertyChangedEvent.GetPropertyName() == GET_MEMBER_NAME_CHECKED(ThisClass, MeshData))
    {
        Refresh();
    }

    Super::PostEditChangeProperty(PropertyChangedEvent);
}
#endif


void UMeshManagerComponent::InitializeComponent()
{
    Super::InitializeComponent();

    FindStaticMeshComponent();
    FindSkeletalMeshComponent();
}

void UMeshManagerComponent::SetStaticMeshComponent(UStaticMeshComponent* NewStaticMeshComponent)
{
    StaticMeshComponent = NewStaticMeshComponent;

    Refresh();
}

void UMeshManagerComponent::SetSkeletalMeshComponent(USkeletalMeshComponent* NewSkeletalMeshComponent)
{
    SkeletalMeshComponent = NewSkeletalMeshComponent;

    Refresh();
}

void UMeshManagerComponent::SetMeshData(UDataAsset* NewMeshData)
{
    MeshData = NewMeshData;

    Refresh();
}

void UMeshManagerComponent::FindStaticMeshComponent()
{
    if (StaticMeshComponent.IsValid()) return;

    auto FoundComponent = GetOwner()->GetComponentByClass<UStaticMeshComponent>();

    if (FoundComponent) SetStaticMeshComponent(FoundComponent);
}

void UMeshManagerComponent::FindSkeletalMeshComponent()
{
    if (SkeletalMeshComponent.IsValid()) return;

    auto FoundComponent = GetOwner()->IsA<ACharacter>()
        ? Cast<ACharacter>(GetOwner())->GetMesh()
        : GetOwner()->GetComponentByClass<USkeletalMeshComponent>();

    if (FoundComponent) SetSkeletalMeshComponent(FoundComponent);
}

UObject* UMeshManagerComponent::GetMeshData() const
{
    return MeshData.GetObject();
}

void UMeshManagerComponent::Refresh()
{
    Clear();

    if (GetMeshData() && GetMeshData()->Implements<UMeshDataInterface>())
    {
        auto SkeletalMesh = IMeshDataInterface::Execute_GetSkeletalMesh(GetMeshData());

        if (SkeletalMeshComponent.IsValid() && !SkeletalMesh.IsNull())
        {
            SetSkeletalMesh();
        }
        else
        {
            SetStaticMesh();
        }
    }
}

void UMeshManagerComponent::Clear()
{
    ClearStaticMesh();
    ClearSkeletalMesh();
}

void UMeshManagerComponent::SetStaticMesh()
{
    if (StaticMeshComponent.IsValid() && GetMeshData() && GetMeshData()->Implements<UMeshDataInterface>())
    {
        auto StaticMesh = IMeshDataInterface::Execute_GetStaticMesh(GetMeshData());
        auto Material = IMeshDataInterface::Execute_GetMaterial(GetMeshData());

        StaticMeshComponent->SetStaticMesh(StaticMesh.LoadSynchronous());
        StaticMeshComponent->SetMaterial(0, Material.LoadSynchronous());
    }
}

void UMeshManagerComponent::ClearStaticMesh()
{
    if (StaticMeshComponent.IsValid())
    {
        StaticMeshComponent->SetStaticMesh(nullptr);
        StaticMeshComponent->SetMaterial(0, nullptr);
    }
}

void UMeshManagerComponent::SetSkeletalMesh()
{
    if (SkeletalMeshComponent.IsValid() && GetMeshData() && GetMeshData()->Implements<UMeshDataInterface>())
    {
        auto SkeletalMesh = IMeshDataInterface::Execute_GetSkeletalMesh(GetMeshData());
        auto Material = IMeshDataInterface::Execute_GetMaterial(GetMeshData());
        auto AnimationClass = IMeshDataInterface::Execute_GetAnimationClass(GetMeshData() );

        SkeletalMeshComponent->SetSkeletalMesh(SkeletalMesh.LoadSynchronous());
        SkeletalMeshComponent->SetMaterial(0, Material.LoadSynchronous());
        SkeletalMeshComponent->SetAnimClass(AnimationClass.LoadSynchronous());
    }
}

void UMeshManagerComponent::ClearSkeletalMesh()
{
    if (SkeletalMeshComponent.IsValid())
    {
        SkeletalMeshComponent->SetSkeletalMesh(nullptr);
        SkeletalMeshComponent->SetMaterial(0, nullptr);
        SkeletalMeshComponent->SetAnimClass(nullptr);
    }
}
