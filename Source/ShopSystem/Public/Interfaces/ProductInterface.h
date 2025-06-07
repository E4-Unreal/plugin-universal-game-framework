// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "ShopGameplayTags.h"
#include "ProductInterface.generated.h"

struct FGameplayTag;

UINTERFACE(MinimalAPI, Blueprintable, BlueprintType)
class UProductInterface : public UInterface
{
    GENERATED_BODY()
};

/**
 *
 */
class SHOPSYSTEM_API IProductInterface
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
    const FGameplayTag GetCurrencyType() const;
    virtual const FGameplayTag GetCurrencyType_Implementation() const { return Currency::Default; }

    UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
    int32 GetBuyPrice() const;

    UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
    int32 GetSellPrice() const;
};
