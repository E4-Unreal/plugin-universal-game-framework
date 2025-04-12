// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "ItemSystemFunctionLibrary.generated.h"

class UItemConfig;
class UItemDefinition;
struct FItemData;

/**
 *
 */
UCLASS()
class ITEMSYSTEM_API UItemSystemFunctionLibrary : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()

    UFUNCTION(BlueprintCallable, meta = (DeterminesOutputType = ItemConfigClass))
    static const UItemConfig* FindItemConfigByClass(UItemDefinition* ItemDefinition, TSubclassOf<UItemConfig> ItemConfigClass);

    UFUNCTION(BlueprintCallable)
    static UItemDefinition* GetItemDefinition(const FItemData& ItemData);
};
