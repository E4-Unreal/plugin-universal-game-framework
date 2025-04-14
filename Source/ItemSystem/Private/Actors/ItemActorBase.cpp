// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/ItemActorBase.h"

#include "Data/ItemDefinition.h"
#include "Types/ActorItemData.h"

FName AItemActorBase::DisplayMeshName(TEXT("DisplayMesh"));

AItemActorBase::AItemActorBase(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer)
{
    /* DisplayMesh */
    DisplayMesh = CreateDefaultSubobject<UStaticMeshComponent>(DisplayMeshName);
}

void AItemActorBase::PostInitializeComponents()
{
    Super::PostInitializeComponents();

    Refresh();
}

void AItemActorBase::Refresh()
{
    if (UItemDefinition* ItemDefinition = ItemContainer.GetItemDefinition())
    {
        if (ItemDefinition->HasData<FActorItemData>())
        {
            const auto& ActorItemData = ItemDefinition->GetData<FActorItemData>();
            DisplayMesh->SetStaticMesh(ActorItemData.StaticMesh.LoadSynchronous());
        }
    }
}
