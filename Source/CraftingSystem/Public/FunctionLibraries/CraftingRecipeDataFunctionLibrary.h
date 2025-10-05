// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "CraftingRecipeDataFunctionLibrary.generated.h"

class UDataDefinitionBase;
struct FItem;

/**
 *
 */
UCLASS()
class CRAFTINGSYSTEM_API UCraftingRecipeDataFunctionLibrary : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()

public:
    /* CraftingRecipeData */

    UFUNCTION(BlueprintPure)
    static UDataAsset* GetCraftingRecipeData(UDataDefinitionBase* Definition);

    UFUNCTION(BlueprintPure)
    static bool HasCraftingRecipeData(UDataDefinitionBase* Definition);

    UFUNCTION(BlueprintPure)
    static TArray<FItem> GetResults(UDataDefinitionBase* Definition);

    UFUNCTION(BlueprintPure)
    static TArray<FItem> GetIngredients(UDataDefinitionBase* Definition);

    UFUNCTION(BlueprintPure)
    static float GetCraftTime(UDataDefinitionBase* Definition);

    UFUNCTION(BlueprintPure)
    static int32 GetToolType(UDataDefinitionBase* Definition);

    UFUNCTION(BlueprintPure)
    static int32 GetToolGrade(UDataDefinitionBase* Definition);
};
