// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/ItemComponentBase.h"


UItemComponentBase::UItemComponentBase()
{
}

void UItemComponentBase::InitializeComponent()
{
    FindDisplayMesh();

    Super::InitializeComponent();
}

void UItemComponentBase::Refresh_Implementation()
{
    if (DisplayMesh.IsValid())
    {
        DisplayMesh->SetStaticMesh(GetStaticMesh());
    }
}

void UItemComponentBase::FindDisplayMesh()
{
    if (DisplayMesh.IsValid()) return;

    DisplayMesh = GetOwner()->FindComponentByClass<UStaticMeshComponent>();
}

UStaticMesh* UItemComponentBase::GetStaticMesh() const
{
    return nullptr;
}
