// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "ShopSystemFunctionLibrary.generated.h"

class IProductInterface;
class ICustomerInterface;
struct FGameplayTag;

/**
 *
 */
UCLASS()
class SHOPSYSTEM_API UShopSystemFunctionLibrary : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintPure, Category = "ProductData")
    static UDataAsset* GetProductData(UObject* DataObject);

    UFUNCTION(BlueprintPure, Category = "ProductData")
    static FGameplayTag GetCurrencyType(UObject* DataObject);

    UFUNCTION(BlueprintPure, Category = "ProductData")
    static int32 GetBuyPrice(UObject* DataObject);

    UFUNCTION(BlueprintPure, Category = "ProductData")
    static int32 GetSellPrice(UObject* DataObject);

    UFUNCTION(BlueprintCallable)
    static bool PurchaseProduct(const TScriptInterface<ICustomerInterface>& Customer, const TScriptInterface<IProductInterface>& Product, int32 Quantity);
};
