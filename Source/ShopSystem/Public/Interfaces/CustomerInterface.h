// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "CustomerInterface.generated.h"

struct FGameplayTag;
class IProductInterface;

UINTERFACE(MinimalAPI, Blueprintable, BlueprintType)
class UCustomerInterface : public UInterface
{
    GENERATED_BODY()
};

/**
 *
 */
class SHOPSYSTEM_API ICustomerInterface
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
    int32 GetCurrency(const FGameplayTag& CurrencyType) const;

    UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
    bool AddCurrency(const FGameplayTag& CurrencyType, int32 Quantity);

    UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
    bool RemoveCurrency(const FGameplayTag& CurrencyType, int32 Quantity);

    UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
    bool AddProduct(const TScriptInterface<IProductInterface>& Product, int32 Quantity);

    UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
    bool RemoveProduct(const TScriptInterface<IProductInterface>& Product, int32 Quantity);
};
