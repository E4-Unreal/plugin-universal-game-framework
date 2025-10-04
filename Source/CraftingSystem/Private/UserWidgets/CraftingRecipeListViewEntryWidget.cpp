// Fill out your copyright notice in the Description page of Project Settings.


#include "CraftingSystem/Public/UserWidgets/CraftingRecipeListViewEntryWidget.h"

#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Data/DataDefinitionBase.h"
#include "FunctionLibraries/CraftingRecipeDataFunctionLibrary.h"
#include "FunctionLibraries/SlotDataFunctionLibrary.h"
#include "Types/Item.h"

void UCraftingRecipeListViewEntryWidget::NativeOnListItemObjectSet(UObject* ListItemObject)
{
    if (auto Recipe = Cast<UDataDefinitionBase>(ListItemObject))
    {
        const FText DisplayName = Recipe->DisplayName;

        const auto& Results = UCraftingRecipeDataFunctionLibrary::GetResults(Recipe);
        if (!Results.IsEmpty())
        {
            const auto& Result = Results[0];
            auto Item = Result.Definition;

            auto ThumbnailTexture = USlotDataFunctionLibrary::GetThumbnailTexture(Item);
            if (GetThumbnailImage())
            {
                GetThumbnailImage()->SetBrushFromSoftTexture(ThumbnailTexture);
            }
        }

        if (GetDisplayNameTextBock())
        {
            GetDisplayNameTextBock()->SetText(DisplayName);
        }
    }
}
