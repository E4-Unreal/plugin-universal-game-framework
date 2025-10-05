// Fill out your copyright notice in the Description page of Project Settings.


#include "UserWidgets/CraftingRecipeViewPanelWidget.h"

#include "CommonButtonBase.h"
#include "Components/CraftingComponent.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Data/DataInstanceBase.h"
#include "FunctionLibraries/CraftingRecipeDataFunctionLibrary.h"
#include "FunctionLibraries/ItemDataFunctionLibrary.h"
#include "FunctionLibraries/SlotDataFunctionLibrary.h"
#include "Types/Item.h"
#include "Widgets/UniformGridView.h"

void UCraftingRecipeViewPanelWidget::SynchronizeProperties()
{
    Super::SynchronizeProperties();

#if WITH_EDITOR
    if (IsDesignTime())
    {
        if (PreviewRecipe)
        {
            SetRecipe(PreviewRecipe);
            SetQuantity(PreviewQuantity);
        }
    }
#endif
}

void UCraftingRecipeViewPanelWidget::NativeOnInitialized()
{
    Super::NativeOnInitialized();

    if (GetCraftButton())
    {
        GetCraftButton()->OnClicked().AddUObject(this, &ThisClass::OnCraftButtonClicked);
    }
}

void UCraftingRecipeViewPanelWidget::Refresh_Implementation()
{
    Super::Refresh_Implementation();

    TSoftObjectPtr<UTexture2D> ThumbnailTexture = nullptr;
    int32 TotalResultQuantity = 0;

    if (GetUniformGridView())
    {
        GetUniformGridView()->ClearEntries();
    }

    if (Recipe && UCraftingRecipeDataFunctionLibrary::HasCraftingRecipeData(Recipe))
    {
        const auto& Results = UCraftingRecipeDataFunctionLibrary::GetResults(Recipe);
        const auto& Ingredients = UCraftingRecipeDataFunctionLibrary::GetIngredients(Recipe);

        if (!Results.IsEmpty())
        {
            const auto& Result = Results[0];
            auto ResultDefinition = Result.Definition;
            int32 ResultQuantity = Result.Quantity;

            ThumbnailTexture = USlotDataFunctionLibrary::GetThumbnailTexture(ResultDefinition);
            TotalResultQuantity = ResultQuantity * Quantity;
        }

        if (GetUniformGridView())
        {
            for (int32 Index = 0; Index < Ingredients.Num(); ++Index)
            {
                const auto& Ingredient = Ingredients[Index];
                if (auto ItemInstance = UItemDataFunctionLibrary::CreateItemInstance(Ingredient.Definition))
                {
                    UItemDataFunctionLibrary::SetQuantity(ItemInstance, Ingredient.Quantity * Quantity);
                    GetUniformGridView()->SetDataObject(Index, ItemInstance);
                }
            }
        }
    }

    SetThumbnailTexture(ThumbnailTexture);
    SetQuantityText(TotalResultQuantity);
}

void UCraftingRecipeViewPanelWidget::SetRecipe(UDataDefinitionBase* NewRecipe)
{
    Recipe = NewRecipe;

    Refresh();
}

void UCraftingRecipeViewPanelWidget::SetQuantity(int32 NewQuantity)
{
    Quantity = NewQuantity;

    Refresh();
}

void UCraftingRecipeViewPanelWidget::SetThumbnailTexture(TSoftObjectPtr<UTexture2D> NewThumbnailTexture)
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

void UCraftingRecipeViewPanelWidget::SetQuantityText(int32 NewQuantity)
{
    NewQuantity = FMath::Min(0, NewQuantity);

    if (GetQuantityTextBlock())
    {
        GetQuantityTextBlock()->SetText(FText::FromString(FString::FromInt(NewQuantity)));
    }
}

void UCraftingRecipeViewPanelWidget::OnCraftButtonClicked()
{
    if (auto CraftingComponent = GetTargetComponent<UCraftingComponent>())
    {
        CraftingComponent->StartCrafting(GetOwningPlayerPawn(), Recipe);
    }
}
