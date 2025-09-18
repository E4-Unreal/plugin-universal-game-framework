// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/ItemComponent.h"

#include "Components/InventoryComponent.h"
#include "Interfaces/DataInstanceInterface.h"
#include "Interfaces/DataInterface.h"
#include "Interfaces/ItemDataInterface.h"
#include "Net/UnrealNetwork.h"

UItemComponent::UItemComponent()
{
    ItemNameFormat = NSLOCTEXT("InventorySystem", "PickupMessage", "{0} +{1}"); // 아이템 외 5개
}

void UItemComponent::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);

    DOREPLIFETIME(ThisClass, Items);
}

#if WITH_EDITOR
void UItemComponent::PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent)
{
    FName PropertyName = PropertyChangedEvent.Property != nullptr ? PropertyChangedEvent.Property->GetFName() : NAME_None;

    if (PropertyName == GET_MEMBER_NAME_CHECKED(ThisClass, Items))
    {
        Refresh();
    }

    Super::PostEditChangeProperty(PropertyChangedEvent);
}
#endif

void UItemComponent::SetItems(const TArray<UObject*> NewItems)
{
    ClearItems();

    Items = NewItems;
    for (const auto& Item : Items)
    {
        AddReplicatedObject(Cast<UReplicatedObject>(Item));
    }

    Refresh();
}

UDataAsset* UItemComponent::GetFirstItemData() const
{
    if (!Items.IsEmpty())
    {
        UObject* FirstItem = Items[0];
        if (FirstItem && FirstItem->Implements<UDataInstanceInterface>())
        {
            UDataAsset* FirstItemData = IDataInstanceInterface::Execute_GetData(FirstItem);
            if (FirstItemData && FirstItemData->Implements<UDataInterface>())
            {
                return FirstItemData;
            }
        }
    }

    return nullptr;
}

void UItemComponent::ClearItems()
{
    for (const auto& Item : Items)
    {
        RemoveReplicatedObject(Cast<UReplicatedObject>(Item));
    }

    Items.Empty();
}

void UItemComponent::OnRep_Items(TArray<UObject*> OldItems)
{
    Refresh();
}

FText UItemComponent::GetItemName() const
{
    if (UDataAsset* FirstItemData = GetFirstItemData())
    {
        FText FirstItemName = IDataInterface::Execute_GetDisplayName(FirstItemData);

        return Items.Num() == 1 ? FirstItemName : FText::Format(ItemNameFormat, FirstItemName);
    }

    return FText::GetEmpty();
}

void UItemComponent::TransferItemsToInventory(AActor* TargetActor)
{
    if (auto InventoryComponent = TargetActor->GetComponentByClass<UInventoryComponent>())
    {
        for (const auto& Item : Items)
        {
            if (Item) InventoryComponent->AddContent(Item);
        }
    }
}

UStaticMesh* UItemComponent::GetStaticMesh() const
{
    UStaticMesh* StaticMesh = nullptr;

    if (Items.Num() == 1)
    {
        UDataAsset* FirstItemData = GetFirstItemData();
        if (FirstItemData && FirstItemData->Implements<UItemDataInterface>())
        {
            StaticMesh = IItemDataInterface::Execute_GetStaticMesh(FirstItemData).LoadSynchronous();
        }
    }
    else if (Items.Num() > 1)
    {
        StaticMesh = GetDefaultItemPackageMesh();
    }

    return StaticMesh ? StaticMesh : GetDefaultItemMesh();
}

UStaticMesh* UItemComponent::GetDefaultItemMesh() const
{
    return DefaultItemMesh.LoadSynchronous();
}

UStaticMesh* UItemComponent::GetDefaultItemPackageMesh() const
{
    return DefaultItemPackageMesh.LoadSynchronous();
}
