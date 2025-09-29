// Fill out your copyright notice in the Description page of Project Settings.


#include "Data/UGFFlexibleItemDataBuilder.h"

#include "Data/ItemDataFragment.h"
#include "Data/MeshDataFragment.h"
#include "Data/ProductDataFragment.h"
#include "Data/UGFFlexibleItemData.h"
#include "Data/UGFItemDataTableRow.h"
#include "Data/WeaponDataFragment.h"

UUGFFlexibleItemDataBuilder::UUGFFlexibleItemDataBuilder()
{
    DataClass = UUGFFlexibleItemData::StaticClass();
    DataName = "Item";
}

bool UUGFFlexibleItemDataBuilder::UpdateData(UDataAsset* Data, FTableRowBase* TableRow)
{
    bool bDirty = false;

    auto ItemData = Cast<UUGFFlexibleItemData>(Data);
    FUGFItemDataTableRow* RowData = static_cast<FUGFItemDataTableRow*>(TableRow);
    if (ItemData && RowData)
    {
        // Data
        SET_TEXT(ItemData->DisplayName, RowData->DisplayName)
        SET_TEXT(ItemData->Description, RowData->Description)

        // Slot
        SET_DATA(ItemData->ThumbnailTexture, RowData->ThumbnailTexture)

        // Mesh
        if (auto MeshDataFragment = ItemData->GetFragmentByClass<UMeshDataFragment>())
        {
            SET_DATA(MeshDataFragment->StaticMesh, RowData->StaticMesh)
            SET_DATA(MeshDataFragment->SkeletalMesh, RowData->SkeletalMesh)
            SET_DATA(MeshDataFragment->Material, RowData->Material)
            SET_DATA(MeshDataFragment->AnimationClass, RowData->AnimationClass)
        }

        // Inventory
        if (auto ItemDataFragment = ItemData->GetFragmentByClass<UItemDataFragment>())
        {
            SET_DATA(ItemDataFragment->MaxStack, RowData->MaxStack)
            SET_DATA(ItemDataFragment->ItemType, RowData->ItemType)
        }

        // Product
        if (auto ProductDataFragment = ItemData->GetFragmentByClass<UProductDataFragment>())
        {
            SET_DATA(ProductDataFragment->CurrencyType, RowData->CurrencyType)
            SET_DATA(ProductDataFragment->BuyPrice, RowData->BuyPrice)
            SET_DATA(ProductDataFragment->SellPrice, RowData->SellPrice)
        }

        // Equipment
        if (auto WeaponDataFragment = ItemData->GetFragmentByClass<UWeaponDataFragment>())
        {
            SET_DATA(WeaponDataFragment->SlotType, RowData->SlotType)
            SET_DATA(WeaponDataFragment->ActiveSocketName, RowData->ActiveSocketName)
            SET_DATA(WeaponDataFragment->InActiveSocketName, RowData->InActiveSocketName)
            SET_DATA(WeaponDataFragment->MaxDurability, RowData->MaxDurability)
        }
    }

    return bDirty;
}
