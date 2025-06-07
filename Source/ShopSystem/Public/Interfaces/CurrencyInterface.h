// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "CurrencyInterface.generated.h"

struct FGameplayTag;

UINTERFACE(MinimalAPI, Blueprintable, BlueprintType)
class UCurrencyInterface : public UInterface
{
    GENERATED_BODY()
};

/**
 *
 */
class SHOPSYSTEM_API ICurrencyInterface
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
    int32 GetCurrency(const FGameplayTag& CurrencyType) const;

    UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
    bool AddCurrency(const FGameplayTag& CurrencyType, int32 Amount);

    UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
    bool RemoveCurrency(const FGameplayTag& CurrencyType, int32 Amount);
};
