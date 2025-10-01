// Fill out your copyright notice in the Description page of Project Settings.


#include "Data/UGFFlexibleItemDataBuilder.h"

#include "Data/ItemDataFragment.h"
#include "Data/MeshDataFragment.h"
#include "Data/ProductDataFragment.h"
#include "Data/SlotDataFragment.h"
#include "Data/UGFFlexibleItemData.h"
#include "Data/UGFItemDataTableRow.h"
#include "Data/WeaponDataFragment.h"

UUGFFlexibleItemDataBuilder::UUGFFlexibleItemDataBuilder()
{
    DefinitionClass = UUGFFlexibleItemData::StaticClass();
    DataName = "Item";
}

bool UUGFFlexibleItemDataBuilder::OnUpdateData(UDataDefinitionBase* Definition, FDataDefinitionTableRowBase* DataDefinitionTableRow)
{
    bool bDirty = false;

    auto ItemData = Cast<UUGFFlexibleItemData>(Definition);
    auto RowData = static_cast<FUGFItemDataTableRow*>(DataDefinitionTableRow);
    if (ItemData && RowData)
    {
        // Slot
        auto SlotDataFragment = ItemData->GetFragmentByClass<USlotDataFragment>();

        if (SlotDataFragment == nullptr)
        {
            SlotDataFragment = ItemData->AddFragment<USlotDataFragment>();
            bDirty = true;
        }

        if (SlotDataFragment)
        {
            SET_DATA(SlotDataFragment->ThumbnailTexture, RowData->ThumbnailTexture)
        }

        // Mesh
        auto MeshDataFragment = ItemData->GetFragmentByClass<UMeshDataFragment>();

        if (MeshDataFragment == nullptr)
        {
            MeshDataFragment = ItemData->AddFragment<UMeshDataFragment>();
            bDirty = true;
        }

        if (MeshDataFragment)
        {
            SET_DATA(MeshDataFragment->StaticMesh, RowData->StaticMesh)
            SET_DATA(MeshDataFragment->SkeletalMesh, RowData->SkeletalMesh)
            SET_DATA(MeshDataFragment->Material, RowData->Material)
            SET_DATA(MeshDataFragment->AnimationClass, RowData->AnimationClass)
        }

        // Inventory
        auto ItemDataFragment = ItemData->GetFragmentByClass<UItemDataFragment>();

        if (ItemDataFragment == nullptr)
        {
            ItemDataFragment = ItemData->AddFragment<UItemDataFragment>();
            bDirty = true;
        }

        if (ItemDataFragment)
        {
            SET_DATA(ItemDataFragment->MaxStack, RowData->MaxStack)
            SET_DATA(ItemDataFragment->ItemType, RowData->ItemType)
        }

        // Product
        auto ProductDataFragment = ItemData->GetFragmentByClass<UProductDataFragment>();

        if (ProductDataFragment == nullptr)
        {
            ProductDataFragment = ItemData->AddFragment<UProductDataFragment>();
            bDirty = true;
        }

        if (ProductDataFragment)
        {
            SET_DATA(ProductDataFragment->CurrencyType, RowData->CurrencyType)
            SET_DATA(ProductDataFragment->BuyPrice, RowData->BuyPrice)
            SET_DATA(ProductDataFragment->SellPrice, RowData->SellPrice)
        }

        // Equipment
        auto WeaponDataFragment = ItemData->GetFragmentByClass<UWeaponDataFragment>();

        if (WeaponDataFragment == nullptr)
        {
            WeaponDataFragment = ItemData->AddFragment<UWeaponDataFragment>();
            bDirty = true;
        }

        if (WeaponDataFragment)
        {
            SET_DATA(WeaponDataFragment->SlotType, RowData->SlotType)
            SET_DATA(WeaponDataFragment->ActiveSocketName, RowData->ActiveSocketName)
            SET_DATA(WeaponDataFragment->InActiveSocketName, RowData->InActiveSocketName)
            SET_DATA(WeaponDataFragment->MaxDurability, RowData->MaxDurability)
        }
    }

    return bDirty;
}
