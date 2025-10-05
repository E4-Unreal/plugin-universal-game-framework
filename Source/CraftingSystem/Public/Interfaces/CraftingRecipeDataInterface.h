// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Types/Item.h"
#include "UObject/Interface.h"
#include "CraftingRecipeDataInterface.generated.h"

UINTERFACE(MinimalAPI, Blueprintable, BlueprintType)
class UCraftingRecipeDataInterface : public UInterface
{
    GENERATED_BODY()
};

/**
 *
 */
class CRAFTINGSYSTEM_API ICraftingRecipeDataInterface
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
    TArray<FItem> GetResults() const;

    UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
    TArray<FItem> GetIngredients() const;

    UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
    float GetCraftTime() const;

    UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
    int32 GetToolType() const;

    UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
    int32 GetToolGrade() const;
};
