// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "ItemInstanceInterface.generated.h"

UINTERFACE(MinimalAPI, Blueprintable, BlueprintType)
class UItemInstanceInterface : public UInterface
{
    GENERATED_BODY()
};

/**
 *
 */
class INVENTORYSYSTEM_API IItemInstanceInterface
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
    int32 GetQuantity() const;

    UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
    void SetQuantity(int32 NewQuantity);
};
