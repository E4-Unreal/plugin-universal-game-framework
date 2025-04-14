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
    SetRootComponent(DisplayMesh);
    DisplayMesh->SetSimulatePhysics(true);
}

void AItemActorBase::PostInitializeComponents()
{
    Super::PostInitializeComponents();

    Refresh();
}

void AItemActorBase::BeginPlay()
{
    Super::BeginPlay();

    if (ItemContainer.IsNotValid())
    {
        Destroy();
    }
}

#if WITH_EDITOR
void AItemActorBase::PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent)
{
    Super::PostEditChangeProperty(PropertyChangedEvent);

    // 변경된 프로퍼티의 이름을 가져온다.
    FName PropertyName = PropertyChangedEvent.Property != nullptr ? PropertyChangedEvent.Property->GetFName() : NAME_None;

    if (PropertyName == GET_MEMBER_NAME_CHECKED(FItemContainer, ID) || PropertyName == GET_MEMBER_NAME_CHECKED(FItemContainer, ItemDefinition))
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
