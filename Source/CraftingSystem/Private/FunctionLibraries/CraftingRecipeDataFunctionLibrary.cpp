// Fill out your copyright notice in the Description page of Project Settings.


#include "FunctionLibraries/CraftingRecipeDataFunctionLibrary.h"

#include "Data/DataDefinitionBase.h"
#include "Interfaces/CraftingRecipeDataInterface.h"

UDataAsset* UCraftingRecipeDataFunctionLibrary::GetCraftingRecipeData(UDataDefinitionBase* Definition)
{
    return Definition ? Definition->GetDataByInterface<UCraftingRecipeDataInterface>() : nullptr;
}

bool UCraftingRecipeDataFunctionLibrary::HasCraftingRecipeData(UDataDefinitionBase* Definition)
{
    return GetCraftingRecipeData(Definition) != nullptr;
}

TArray<FItem> UCraftingRecipeDataFunctionLibrary::GetResults(UDataDefinitionBase* Definition)
{
    if (auto Data = GetCraftingRecipeData(Definition))
    {
        return ICraftingRecipeDataInterface::Execute_GetResults(Data);
    }

    return TArray<FItem>();
}

TArray<FItem> UCraftingRecipeDataFunctionLibrary::GetIngredients(UDataDefinitionBase* Definition)
{
    if (auto Data = GetCraftingRecipeData(Definition))
    {
        return ICraftingRecipeDataInterface::Execute_GetIngredients(Data);
    }

    return TArray<FItem>();
}

float UCraftingRecipeDataFunctionLibrary::GetCraftTime(UDataDefinitionBase* Definition)
{
    if (auto Data = GetCraftingRecipeData(Definition))
    {
        return ICraftingRecipeDataInterface::Execute_GetCraftTime(Data);
    }

    return 0.0f;
}

int32 UCraftingRecipeDataFunctionLibrary::GetToolType(UDataDefinitionBase* Definition)
{
    if (auto Data = GetCraftingRecipeData(Definition))
    {
        return ICraftingRecipeDataInterface::Execute_GetToolType(Data);
    }

    return 0;
}

int32 UCraftingRecipeDataFunctionLibrary::GetToolGrade(UDataDefinitionBase* Definition)
{
    if (auto Data = GetCraftingRecipeData(Definition))
    {
        return ICraftingRecipeDataInterface::Execute_GetToolGrade(Data);
    }

    return 0;
}
