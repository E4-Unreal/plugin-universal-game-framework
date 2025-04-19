// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/ItemActor.h"

#include "Components/InventoryComponent.h"
#include "Interfaces/InventoryItemDataInterface.h"
#include "Types/InventoryItemData.h"

AItemActor::AItemActor(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer)
{
    auto DisplayStaticMesh = GetDisplayStaticMesh();
    DisplayStaticMesh->SetSimulatePhysics(true);
}

void AItemActor::PostInitializeComponents()
{
    Super::PostInitializeComponents();

    Refresh();
}

void AItemActor::BeginPlay()
{
    if (InventoryItemList.IsEmpty())
    {
        Destroy();
    }
    else
    {
        for (const auto& InventoryItem : InventoryItemList)
        {
            if (InventoryItem.GetData().IsNotValid())
            {
                Destroy();
                break;
            }
        }
    }

    Super::BeginPlay();
}

#if WITH_EDITOR
void AItemActor::PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent)
{
    Super::PostEditChangeProperty(PropertyChangedEvent);

    FName PropertyName = PropertyChangedEvent.Property != nullptr ? PropertyChangedEvent.Property->GetFName() : NAME_None;

    if (PropertyName == GET_MEMBER_NAME_CHECKED(ThisClass, DefaultStaticMesh) ||
        PropertyName == GET_MEMBER_NAME_CHECKED(ThisClass, InventoryItemList) ||
        PropertyName == GET_MEMBER_NAME_CHECKED(FInventoryItem, Item)
        )
    {
        Refresh();
    }
}
#endif

void AItemActor::OnInteract_Implementation(AActor* Interactor)
{
    Super::OnInteract_Implementation(Interactor);

    if (auto InventoryComponent = Interactor->GetComponentByClass<UInventoryComponent>())
    {
        for (const auto& InventoryItem : InventoryItemList)
        {
            if (InventoryItem.GetData().IsValid()) InventoryComponent->AddItem(InventoryItem.Item, InventoryItem.Quantity);
        }

        Destroy();
    }
}

void AItemActor::Refresh()
{
    GetDisplayStaticMesh()->SetStaticMesh(GetStaticMesh());
}

UStaticMesh* AItemActor::GetStaticMesh() const
{
    if (InventoryItemList.Num() != 1) return DefaultStaticMesh;

    auto StaticMesh = InventoryItemList[0].GetData().StaticMesh.LoadSynchronous();

    return StaticMesh ? StaticMesh : DefaultStaticMesh.Get();
}
