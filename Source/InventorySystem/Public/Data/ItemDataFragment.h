// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Data/Flexible/DataFragment.h"
#include "Interfaces/ItemDataInterface.h"
#include "ItemDataFragment.generated.h"

/**
 *
 */
UCLASS()
class INVENTORYSYSTEM_API UItemDataFragment : public UDataFragment, public IItemDataInterface
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config", meta = (ClampMin = 1))
    int32 MaxStack;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config", meta = (Categories = "Item"))
    FGameplayTag ItemType;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
    TSoftObjectPtr<UMaterialInterface> Material;

public:
    UItemDataFragment();

    /* ItemDataInterface */

    virtual int32 GetMaxStack_Implementation() const override { return MaxStack; }
    virtual FGameplayTag GetItemType_Implementation() const override { return ItemType; }
    virtual TSoftObjectPtr<UMaterialInterface> GetMaterial_Implementation() const override { return Material; }
};
