// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "ProductDataFunctionLibrary.generated.h"

class UDataDefinitionBase;
struct FGameplayTag;

/**
 *
 */
UCLASS()
class SHOPSYSTEM_API UProductDataFunctionLibrary : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()

public:
    /* ProductData */

    UFUNCTION(BlueprintPure, Category = "ProductData")
    static bool HasProductData(UDataDefinitionBase* Definition);

    UFUNCTION(BlueprintPure, Category = "ProductData")
    static FGameplayTag GetCurrencyType(UDataDefinitionBase* Definition);

    UFUNCTION(BlueprintPure, Category = "ProductData")
    static int32 GetBuyPrice(UDataDefinitionBase* Definition);

    UFUNCTION(BlueprintPure, Category = "ProductData")
    static int32 GetSellPrice(UDataDefinitionBase* Definition);

protected:
    static UDataAsset* GetProductData(UDataDefinitionBase* Definition);
};
