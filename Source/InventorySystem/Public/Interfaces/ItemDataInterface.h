// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "UObject/Interface.h"
#include "ItemDataInterface.generated.h"

UINTERFACE(MinimalAPI, Blueprintable, BlueprintType)
class UItemDataInterface : public UInterface
{
    GENERATED_BODY()
};

/**
 *
 */
class INVENTORYSYSTEM_API IItemDataInterface
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
    FGameplayTag GetItemType() const;
};
