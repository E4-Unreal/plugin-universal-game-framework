// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Types/Item.h"
#include "Data/DataDefinitionBase.h"
#include "CraftingRecipeDefinition.generated.h"

/**
 *
 */
UCLASS()
class CRAFTINGSYSTEM_API UCraftingRecipeDefinition : public UDataDefinitionBase
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
    TArray<FItem> Results;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
    TArray<FItem> Ingredients;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config", meta = (ClampMin = 0))
    float CraftTime;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config", meta = (ClampMin = 0))
    int32 ToolType;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config", meta = (ClampMin = 0))
    int32 ToolGrade;
};
