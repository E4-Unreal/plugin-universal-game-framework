// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "GameplayTagContainer.h"
#include "Types/InventoryItemData.h"
#include "UGFItemDefinitionDataTableRow.generated.h"

USTRUCT(BlueprintType)
struct FUGFItemDefinitionDataTableRow : public FTableRowBase
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FText DisplayText;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ClampMin = 1))
    int32 MaxStack = 1;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FGameplayTagContainer ItemTypes;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool bCanEquip = false;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool bCanUse = false;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TSoftObjectPtr<UStaticMesh> StaticMesh;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TSoftObjectPtr<UTexture2D> ThumbnailTexture;

    FInventoryItemData GetInventoryItemData() const
    {
        FInventoryItemData InventoryItemData;
        InventoryItemData.DisplayText = DisplayText;
        InventoryItemData.MaxStack = MaxStack;
        InventoryItemData.ItemTypes = ItemTypes;
        InventoryItemData.bCanEquip = bCanEquip;
        InventoryItemData.bCanUse = bCanUse;
        InventoryItemData.StaticMesh = StaticMesh;
        InventoryItemData.ThumbnailTexture = ThumbnailTexture;

        return InventoryItemData;
    }
};
