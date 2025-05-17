// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "InventoryItemData.generated.h"

USTRUCT(Atomic, BlueprintType)
struct INVENTORYSYSTEM_API FInventoryItemData
{
    GENERATED_BODY()

    static const FInventoryItemData Empty;

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

    FInventoryItemData() {}
    FInventoryItemData(int32 InMaxStack)
    {
        MaxStack = InMaxStack;
    }

    FORCEINLINE bool IsValid() const { return MaxStack > 0; }
    FORCEINLINE bool IsNotValid() const { return !IsValid(); }

    FORCEINLINE bool operator==(const FInventoryItemData& Other) const
    {
        return DisplayText.EqualTo(Other.DisplayText)
        && MaxStack == Other.MaxStack
        && ItemTypes == Other.ItemTypes
        && bCanEquip == Other.bCanEquip
        && bCanUse == Other.bCanUse
        && StaticMesh == Other.StaticMesh
        && ThumbnailTexture == Other.ThumbnailTexture;
    }
};
