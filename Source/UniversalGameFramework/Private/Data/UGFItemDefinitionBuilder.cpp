// Fill out your copyright notice in the Description page of Project Settings.


#include "Data/UGFItemDefinitionBuilder.h"

#include "Data/ItemDataFragment.h"
#include "Data/MeshDataFragment.h"
#include "Data/ProductDataFragment.h"
#include "Data/SlotDataFragment.h"
#include "Data/UGFItemDefinition.h"
#include "Data/UGFItemDataTableRow.h"
#include "Data/WeaponDataFragment.h"

UUGFItemDefinitionBuilder::UUGFItemDefinitionBuilder()
{
    DefinitionClass = UUGFItemDefinition::StaticClass();
    DataName = "Item";
}

bool UUGFItemDefinitionBuilder::OnUpdateData(UDataDefinitionBase* Definition, FDataDefinitionTableRowBase* DataDefinitionTableRow)
{
    bool bDirty = false;

    auto ItemDefinition = Cast<UFlexibleDataDefinition>(Definition);
    auto RowData = static_cast<FUGFItemDataTableRow*>(DataDefinitionTableRow);
    if (ItemDefinition && RowData)
    {
        // SlotData
        if (auto SlotData = ItemDefinition->AddFragment<USlotDataFragment>())
        {
            SET_DATA(SlotData->ThumbnailTexture, RowData->ThumbnailTexture)
        }

        // MeshData
        if (auto MeshData = ItemDefinition->AddFragment<UMeshDataFragment>())
        {
            SET_DATA(MeshData->StaticMesh, RowData->StaticMesh)
            SET_DATA(MeshData->SkeletalMesh, RowData->SkeletalMesh)
            SET_DATA(MeshData->Material, RowData->Material)
            SET_DATA(MeshData->AnimationClass, RowData->AnimationClass)
        }

        // ItemData
        if (auto ItemData = ItemDefinition->AddFragment<UItemDataFragment>())
        {
            SET_DATA(ItemData->MaxStack, RowData->MaxStack)
            SET_DATA(ItemData->ItemType, RowData->ItemType)
        }

        // ProductData
        if (auto ProductData = ItemDefinition->AddFragment<UProductDataFragment>())
        {
            SET_DATA(ProductData->CurrencyType, RowData->CurrencyType)
            SET_DATA(ProductData->BuyPrice, RowData->BuyPrice)
            SET_DATA(ProductData->SellPrice, RowData->SellPrice)
        }

        // WeaponData
        if (auto WeaponData = ItemDefinition->AddFragment<UWeaponDataFragment>())
        {
            SET_DATA(WeaponData->SlotType, RowData->SlotType)
            SET_DATA(WeaponData->ActiveSocketName, RowData->ActiveSocketName)
            SET_DATA(WeaponData->InActiveSocketName, RowData->InActiveSocketName)
            SET_DATA(WeaponData->MaxDurability, RowData->MaxDurability)
        }
    }

    return bDirty;
}
