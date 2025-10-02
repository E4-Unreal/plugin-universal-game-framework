// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Data/Flexible/DataFragment.h"
#include "Interfaces/ProductDataInterface.h"
#include "ProductDataFragment.generated.h"

/**
 *
 */
UCLASS()
class SHOPSYSTEM_API UProductDataFragment : public UDataFragment, public IProductDataInterface
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config", meta = (Categories = "Currency"))
    FGameplayTag CurrencyType;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config", meta = (ClampMin = 0))
    int32 BuyPrice;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config", meta = (ClampMin = 0))
    int32 SellPrice;

public:
    UProductDataFragment();

    /* ProductInterface */

    virtual const FGameplayTag GetCurrencyType_Implementation() const override { return CurrencyType; }
    virtual int32 GetBuyPrice_Implementation() const override { return BuyPrice; }
    virtual int32 GetSellPrice_Implementation() const override { return SellPrice; }
};
