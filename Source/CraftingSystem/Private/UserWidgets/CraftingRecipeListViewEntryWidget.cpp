// Fill out your copyright notice in the Description page of Project Settings.


#include "CraftingSystem/Public/UserWidgets/CraftingRecipeListViewEntryWidget.h"

#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Data/DataDefinitionBase.h"
#include "FunctionLibraries/CraftingRecipeDataFunctionLibrary.h"
#include "FunctionLibraries/SlotDataFunctionLibrary.h"
#include "Types/Item.h"

void UCraftingRecipeListViewEntryWidget::SynchronizeProperties()
{
    Super::SynchronizeProperties();

#if WITH_EDITOR
    if (IsDesignTime())
    {
        if (PreviewRecipe)
        {
            SetRecipe(PreviewRecipe);
        }
    }
#endif
}

void UCraftingRecipeListViewEntryWidget::SetDisplayName(const FText& NewDisplayName)
{
    if (GetDisplayNameTextBlock())
    {
        GetDisplayNameTextBlock()->SetText(NewDisplayName);
    }
}

void UCraftingRecipeListViewEntryWidget::SetThumbnailTexture(TSoftObjectPtr<UTexture2D> NewThumbnailTexture)
{
    if (GetThumbnailImage())
    {
        if (NewThumbnailTexture.IsNull())
        {
            GetThumbnailImage()->SetBrushTintColor(FSlateColor(FLinearColor::Transparent));
        }
        else
        {
            GetThumbnailImage()->SetBrushTintColor(FSlateColor(FLinearColor::White));
            GetThumbnailImage()->SetBrushFromSoftTexture(NewThumbnailTexture);
        }
    }
}

void UCraftingRecipeListViewEntryWidget::SetRecipe(UDataDefinitionBase* NewRecipe)
{
    FText DisplayName;
    TSoftObjectPtr<UTexture2D> ThumbnailTexture;

    if (NewRecipe)
    {
        const auto& Results = UCraftingRecipeDataFunctionLibrary::GetResults(NewRecipe);
        if (!Results.IsEmpty())
        {
            const auto& Item = Results[0];
            auto ItemDefinition = Item.Definition;
            DisplayName = ItemDefinition->DisplayName;
            ThumbnailTexture = USlotDataFunctionLibrary::GetThumbnailTexture(ItemDefinition);
        }
    }

    SetDisplayName(DisplayName);
    SetThumbnailTexture(ThumbnailTexture);
}

void UCraftingRecipeListViewEntryWidget::NativeOnListItemObjectSet(UObject* ListItemObject)
{
    SetRecipe(Cast<UDataDefinitionBase>(ListItemObject));
}
