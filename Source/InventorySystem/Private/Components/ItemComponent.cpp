// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/ItemComponent.h"

#include "Components/InventoryComponent.h"
#include "Data/DataDefinitionBase.h"
#include "Data/DataInstanceBase.h"
#include "FunctionLibraries/DataManagerFunctionLibrary.h"
#include "FunctionLibraries/MeshDataFunctionLibrary.h"
#include "Net/UnrealNetwork.h"
#include "Settings/InventorySystemSettings.h"

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

bool UItemComponent::AddItemsToInventory(AActor* TargetActor)
{
    if (Super::AddItemsToInventory(TargetActor))
    {
        GetOwner()->Destroy();

        return true;
    }

    return false;
}
#endif

void UItemComponent::SetItems(const TArray<UDataInstanceBase*> NewItems)
{
    ClearItems();

    Items = NewItems;
    for (const auto& Item : Items)
    {
        AddReplicatedObject(Cast<UReplicatedObject>(Item));
    }

    Refresh();
}

void UItemComponent::ClearItems()
{
    for (const auto& Item : Items)
    {
        RemoveReplicatedObject(Cast<UReplicatedObject>(Item));
    }

    Items.Empty();
}

void UItemComponent::OnRep_Items(TArray<UDataInstanceBase*> OldItems)
{
    Refresh();
}

FText UItemComponent::GetItemName() const
{
    if (!Items.IsEmpty())
    {
        if (auto Definition = Items[0]->Definition)
        {
            FText FirstItemName = Definition->DisplayName;

            return Items.Num() == 1 ? FirstItemName : FText::Format(ItemNameFormat, FirstItemName);
        }
    }

    return FText::GetEmpty();
}

UStaticMesh* UItemComponent::GetStaticMesh() const
{
    UStaticMesh* StaticMesh = nullptr;

    if (Items.Num() == 1)
    {
        StaticMesh = UMeshDataFunctionLibrary::GetStaticMesh(Items[0]->Definition).LoadSynchronous();
    }
    else if (Items.Num() > 1)
    {
        StaticMesh = GetDefaultItemPackageMesh();
    }

    return StaticMesh ? StaticMesh : GetDefaultItemMesh();
}

UMaterialInterface* UItemComponent::GetMaterial() const
{
    UMaterialInterface* Material = nullptr;

    if (Items.Num() == 1)
    {
        Material = UMeshDataFunctionLibrary::GetMaterial(Items[0]->Definition).LoadSynchronous();
    }

    return Material;
}

UStaticMesh* UItemComponent::GetDefaultItemMesh() const
{
    return !DefaultItemMesh.IsNull() ? DefaultItemMesh.LoadSynchronous() : UInventorySystemSettings::Get()->GetDefaultItemMesh();
}

UStaticMesh* UItemComponent::GetDefaultItemPackageMesh() const
{
    return !DefaultItemPackageMesh.IsNull() ? DefaultItemPackageMesh.LoadSynchronous() : UInventorySystemSettings::Get()->GetDefaultItemPackageMesh();
}
