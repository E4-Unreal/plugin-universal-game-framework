// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Data/Flexible/FlexibleData.h"
#include "Interfaces/ItemDataInterface.h"
#include "Interfaces/MeshDataInterface.h"
#include "Interfaces/ProductInterface.h"
#include "Interfaces/SlotDataInterface.h"
#include "Interfaces/WeaponDataInterface.h"
#include "UGFFlexibleItemData.generated.h"

class UItemDataFragment;

/**
 *
 */
UCLASS()
class UNIVERSALGAMEFRAMEWORK_API UUGFFlexibleItemData : public UFlexibleData,
    public IProductInterface
{
    GENERATED_BODY()

public:
    UUGFFlexibleItemData(const FObjectInitializer& ObjectInitializer);

    /* PrimaryDataAsset */

    virtual FPrimaryAssetId GetPrimaryAssetId() const override;

    /* ProductInterface */

    virtual FText GetDisplayNameText_Implementation() const override { return DisplayName; }
    virtual const FGameplayTag GetCurrencyType_Implementation() const override;
    virtual int32 GetBuyPrice_Implementation() const override;
    virtual int32 GetSellPrice_Implementation() const override;
};
