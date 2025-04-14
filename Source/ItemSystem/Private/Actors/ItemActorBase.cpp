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

#if WITH_EDITOR
void AItemActorBase::PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent)
{
    Super::PostEditChangeProperty(PropertyChangedEvent);

    FName PropertyName = PropertyChangedEvent.Property != nullptr ? PropertyChangedEvent.Property->GetFName() : NAME_None;
    if (PropertyName == GET_MEMBER_NAME_CHECKED(AItemActorBase, ItemContainer.ID) || PropertyName == GET_MEMBER_NAME_CHECKED(AItemActorBase, ItemContainer.ItemDefinition))
    {
        Refresh();
    }
}
#endif

void AItemActorBase::Refresh()
{
    if (UItemDefinition* ItemDefinition = ItemContainer.GetItemDefinition())
    {
        if (ItemDefinition->HasData<FActorItemData>())
        {
            const auto& ActorItemData = ItemDefinition->GetData<FActorItemData>();
            UStaticMesh* StaticMesh = ActorItemData.StaticMesh.LoadSynchronous();
            if (StaticMesh == nullptr) StaticMesh = DefaultStaticMesh;
            DisplayMesh->SetStaticMesh(StaticMesh);

            return;
        }
    }

    DisplayMesh->SetStaticMesh(DefaultStaticMesh);
}
