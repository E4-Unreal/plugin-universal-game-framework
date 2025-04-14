// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "ItemSystemFunctionLibrary.generated.h"

class UItemDefinition;
struct FItemContainer;

/**
 *
 */
UCLASS()
class ITEMSYSTEM_API UItemSystemFunctionLibrary : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()

    UFUNCTION(BlueprintCallable)
    static UItemDefinition* GetItemDefinition(const FItemContainer& ItemData);
};
