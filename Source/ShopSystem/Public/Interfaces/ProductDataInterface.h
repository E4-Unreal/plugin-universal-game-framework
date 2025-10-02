// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "GameplayTagContainer.h"
#include "ProductDataInterface.generated.h"

UINTERFACE(MinimalAPI, Blueprintable, BlueprintType)
class UProductDataInterface : public UInterface
{
    GENERATED_BODY()
};

/**
 *
 */
class SHOPSYSTEM_API IProductDataInterface
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
    const FGameplayTag GetCurrencyType() const;

    UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
    int32 GetBuyPrice() const;

    UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
    int32 GetSellPrice() const;
};
