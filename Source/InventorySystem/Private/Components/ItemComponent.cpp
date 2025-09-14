// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/ItemComponent.h"

#include "Components/InventoryComponent.h"
#include "Data/DataInstanceBase.h"
#include "Interfaces/ItemDataInterface.h"


UItemComponent::UItemComponent(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer)
{
    bWantsInitializeComponent = true;

    bAutoDestroy = true;
    ItemNameFormat = NSLOCTEXT("InventorySystem", "PickupMessage", "{0} +{1}"); // 아이템 외 5개
}

void UItemComponent::InitializeComponent()
{
    Super::InitializeComponent();

    FindDisplayMesh();
    Refresh();
}

void UItemComponent::BeginPlay()
{
    if (ItemInstances.IsEmpty())
    {
        GetOwner()->Destroy();
    }
    else
    {
        Super::BeginPlay();
    }
}

void UItemComponent::SetDisplayMesh(UStaticMeshComponent* NewDisplayMesh)
{
    DisplayMesh = NewDisplayMesh;
}

void UItemComponent::FindDisplayMesh()
{
    if (DisplayMesh.IsValid()) return;

    DisplayMesh = GetOwner()->FindComponentByClass<UStaticMeshComponent>();
}

FText UItemComponent::GetItemName() const
{
    if (!ItemInstances.IsEmpty())
    {
        auto Data = ItemInstances[0]->GetData();
        if (Data && Data->Implements<UItemDataInterface>())
        {
            FText ItemDisplayName = IItemDataInterface::Execute_GetDisplayNameText(Data);

            return ItemInstances.Num() == 1 ? ItemDisplayName : FText::Format(ItemNameFormat, ItemDisplayName, FText::FromString(FString::FromInt(ItemInstances.Num() - 1)));
        }
    }

    return FText::GetEmpty();
}

void UItemComponent::SetItems(const TArray<UDataInstanceBase*>& NewItemInstances)
{
    ItemInstances = NewItemInstances;

    Refresh();
}

void UItemComponent::TransferItemsToInventory(AActor* TargetActor)
{
    if (auto InventoryComponent = TargetActor->GetComponentByClass<UInventoryComponent>())
    {
        for (const auto& InventoryItem : ItemInstances)
        {
            if (InventoryItem) InventoryComponent->AddContent(InventoryItem);
        }

        ItemInstances.Empty();

        if (bAutoDestroy) GetOwner()->Destroy();
    }
}

#if WITH_EDITOR
void UItemComponent::PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent)
{
    Super::PostEditChangeProperty(PropertyChangedEvent);

    FName PropertyName = PropertyChangedEvent.Property != nullptr ? PropertyChangedEvent.Property->GetFName() : NAME_None;

    if (PropertyName == GET_MEMBER_NAME_CHECKED(ThisClass, DefaultStaticMesh) ||
        PropertyName == GET_MEMBER_NAME_CHECKED(ThisClass, ItemInstances)
        )
    {
        Refresh();
    }
}
#endif

void UItemComponent::Refresh()
{
    if (DisplayMesh.IsValid())
    {
        DisplayMesh->SetStaticMesh(GetStaticMesh());
    }
}

UStaticMesh* UItemComponent::GetStaticMesh() const
{
    UStaticMesh* StaticMesh = nullptr;

    if (ItemInstances.Num() == 1)
    {
        if (auto ItemInstance = ItemInstances.Last())
        {
            if (UDataAsset* Data = ItemInstance->GetData())
            {
                if (Data->Implements<UItemDataInterface>())
                {
                    StaticMesh = IItemDataInterface::Execute_GetStaticMesh(Data).LoadSynchronous();
                }
            }
        }
    }

    return StaticMesh ? StaticMesh : DefaultStaticMesh.LoadSynchronous();
}
