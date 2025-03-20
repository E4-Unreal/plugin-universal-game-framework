// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Types/UGFItem.h"
#include "UGFItemSystemFunctionLibrary.generated.h"

class UUGFItemConfig;
class UUGFItemDefinition;

/**
 *
 */
UCLASS()
class UGFITEMSYSTEM_API UUGFItemSystemFunctionLibrary : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()

    UFUNCTION(BlueprintCallable, meta = (DeterminesOutputType = ItemConfigClass))
    static const UUGFItemConfig* FindItemConfigByClass(UUGFItemDefinition* ItemDefinition, TSubclassOf<UUGFItemConfig> ItemConfigClass);

public:
    UFUNCTION(BlueprintPure)
    static bool IsValidItem(const FUGFItem& Item);
};
