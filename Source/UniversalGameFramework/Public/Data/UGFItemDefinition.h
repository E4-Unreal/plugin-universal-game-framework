// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DynamicData/Public/Data/DefinitionBase.h"
#include "Interfaces/InventoryItemDataInterface.h"
#include "Interfaces/ProductInterface.h"
#include "Types/InventoryItemData.h"
#include "GameplayTags/CurrencyGameplayTags.h"
#include "UGFItemDefinition.generated.h"

/**
 *
 */
UCLASS()
class UNIVERSALGAMEFRAMEWORK_API UUGFItemDefinition : public UDefinitionBase,
    public IInventoryItemDataInterface,
    public IProductInterface
{
    GENERATED_BODY()

protected:
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Config")
    FText DisplayNameText;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Config")
    TSoftObjectPtr<UTexture2D> ThumbnailTexture;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Config", meta = (Categories = "Currency"))
    FGameplayTag CurrencyType = Currency::Default;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Config")
    int32 BuyPrice;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Config")
    int32 SellPrice;

public:
    /* InventoryItemDataInterface */

    virtual const FInventoryItemData GetInventoryItemData_Implementation() const override { return GetData<FInventoryItemData>(); }

    /* ProductInterface */

    virtual FText GetDisplayNameText_Implementation() const override { return DisplayNameText; }
    virtual TSoftObjectPtr<UTexture2D> GetThumbnailTexture_Implementation() const override { return ThumbnailTexture; }
    virtual const FGameplayTag GetCurrencyType_Implementation() const override { return CurrencyType; }
    virtual int32 GetBuyPrice_Implementation() const override { return BuyPrice; }
    virtual int32 GetSellPrice_Implementation() const override { return SellPrice; }
};
