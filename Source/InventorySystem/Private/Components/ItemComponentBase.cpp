// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/ItemComponentBase.h"

#include "Components/InventoryComponent.h"


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
        DisplayMesh->SetMaterial(0, GetMaterial());
    }
}

bool UItemComponentBase::AddItemsToInventory(AActor* TargetActor)
{
    if (auto InventoryComponent = TargetActor->GetComponentByClass<UInventoryComponent>())
    {
        for (const auto& Item : GetItems())
        {
            if (Item) InventoryComponent->AddContent(Item);
        }

        return true;
    }

    return false;
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

UMaterialInterface* UItemComponentBase::GetMaterial() const
{
    return nullptr;
}
