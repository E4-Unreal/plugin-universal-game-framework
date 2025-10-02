// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "ShopSystemFunctionLibrary.generated.h"

class ICustomerInterface;
class UDataDefinitionBase;
struct FGameplayTag;

/**
 *
 */
UCLASS()
class SHOPSYSTEM_API UShopSystemFunctionLibrary : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable)
    static bool PurchaseProduct(AActor* Customer, UDataDefinitionBase* Product, int32 Quantity);
};
