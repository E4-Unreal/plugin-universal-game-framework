// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/ItemActor.h"

#include "Components/InventoryComponent.h"

AItemActor::AItemActor(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer)
{
    auto DisplayStaticMesh = GetDisplayStaticMesh();
    DisplayStaticMesh->SetSimulatePhysics(true);
}

void AItemActor::SetInventoryItems_Implementation(const TArray<FItemInstance>& NewInventoryItems)
{
    InventoryItems = NewInventoryItems;

    Refresh();
}

void AItemActor::PostInitializeComponents()
{
    Super::PostInitializeComponents();

    Refresh();
}

void AItemActor::BeginPlay()
{
    if (InventoryItems.IsEmpty())
    {
        Destroy();
    }
    else
    {
        for (const auto& InventoryItem : InventoryItems)
        {
            if (!InventoryItem.IsValid())
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
        PropertyName == GET_MEMBER_NAME_CHECKED(ThisClass, InventoryItems) ||
        PropertyName == GET_MEMBER_NAME_CHECKED(FItemInstance, Data)
        )
    {
        Refresh();
    }
}
#endif

void AItemActor::OnInteractionTriggered_Implementation(AActor* Interactor)
{
    Super::OnInteractionTriggered_Implementation(Interactor);

    if (auto InventoryComponent = Interactor->GetComponentByClass<UInventoryComponent>())
    {
        for (const auto& InventoryItem : InventoryItems)
        {
            if (InventoryItem.IsValid()) InventoryComponent->AddItem(InventoryItem);
        }

        if (bAutoDestroy) Destroy();
    }
}

void AItemActor::Refresh()
{
    GetDisplayStaticMesh()->SetStaticMesh(GetStaticMesh());
}

UStaticMesh* AItemActor::GetStaticMesh() const
{
    UStaticMesh* StaticMesh = nullptr;

    if (InventoryItems.Num() == 1 && InventoryItems[0].Data)
    {
        StaticMesh = IItemDataInterface::Execute_GetStaticMesh(InventoryItems[0].Data.GetObject()).LoadSynchronous();
    }

    return StaticMesh ? StaticMesh : DefaultStaticMesh.LoadSynchronous();
}
