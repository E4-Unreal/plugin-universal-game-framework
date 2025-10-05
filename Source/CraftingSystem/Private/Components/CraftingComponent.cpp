// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/CraftingComponent.h"

#include "Components/InventoryComponent.h"
#include "Data/DataInstanceBase.h"
#include "FunctionLibraries/CraftingRecipeDataFunctionLibrary.h"
#include "FunctionLibraries/ItemDataFunctionLibrary.h"
#include "Types/Item.h"


UCraftingComponent::UCraftingComponent()
{
    bWantsInitializeComponent = true;
}

void UCraftingComponent::InitializeComponent()
{
    Super::InitializeComponent();

    AddDefaultRecipes();
}

bool UCraftingComponent::HasRecipe(UDataDefinitionBase* InRecipe) const
{
    return InRecipe && Recipes.Contains(InRecipe);
}

bool UCraftingComponent::CanAddRecipe(UDataDefinitionBase* NewRecipe) const
{
    if (HasRecipe(NewRecipe) || !UCraftingRecipeDataFunctionLibrary::HasCraftingRecipeData(NewRecipe)) return false;

    const TArray<FItem> RecipeResults = UCraftingRecipeDataFunctionLibrary::GetResults(NewRecipe);
    const int32 RecipeToolType = UCraftingRecipeDataFunctionLibrary::GetToolType(NewRecipe);
    const int32 RecipeToolGrade = UCraftingRecipeDataFunctionLibrary::GetToolGrade(NewRecipe);

    return !RecipeResults.IsEmpty() && RecipeToolType <= ToolType && RecipeToolGrade <= ToolGrade;
}

void UCraftingComponent::AddRecipe(UDataDefinitionBase* NewRecipe)
{
    if (!CanAddRecipe(NewRecipe)) return;

    Recipes.Emplace(NewRecipe);
}

bool UCraftingComponent::IsCrafting() const
{
    return GetWorld()->GetTimerManager().TimerExists(CraftingTimerHandle);
}

bool UCraftingComponent::CanCraft(AActor* Crafter, UDataDefinitionBase* InRecipe) const
{
    return !IsCrafting() && HasIngredients(Crafter, InRecipe) && HasRecipe(InRecipe);
}

void UCraftingComponent::StartCrafting(AActor* Crafter, UDataDefinitionBase* InRecipe)
{
    if (!CanCraft(Crafter, InRecipe)) return;

    const float CraftTime = UCraftingRecipeDataFunctionLibrary::GetCraftTime(InRecipe);

    if (CraftTime <= 0.0f)
    {
        OnCraftingFinished(Crafter, InRecipe);
    }
    else
    {
        FTimerDelegate CraftingTimerDelegate;
        CraftingTimerDelegate.BindLambda([&, Crafter, InRecipe]()
        {
            OnCraftingFinished(Crafter, InRecipe);
        });
        GetWorld()->GetTimerManager().SetTimer(CraftingTimerHandle, CraftingTimerDelegate, CraftTime, false);
    }
}

void UCraftingComponent::PauseCrafting()
{
    FTimerManager& TimerManager = GetWorld()->GetTimerManager();
    if (TimerManager.IsTimerActive(CraftingTimerHandle))
    {
        TimerManager.PauseTimer(CraftingTimerHandle);
    }
}

void UCraftingComponent::ResumeCrafting()
{
    FTimerManager& TimerManager = GetWorld()->GetTimerManager();
    if (TimerManager.IsTimerPaused(CraftingTimerHandle))
    {
        TimerManager.UnPauseTimer(CraftingTimerHandle);
    }
}

void UCraftingComponent::StopCrafting()
{
    FTimerManager& TimerManager = GetWorld()->GetTimerManager();
    if (TimerManager.TimerExists(CraftingTimerHandle))
    {
        TimerManager.ClearTimer(CraftingTimerHandle);
    }
}

void UCraftingComponent::AddDefaultRecipes()
{
    for (auto Recipe : DefaultRecipes)
    {
        AddRecipe(Recipe);
    }
}

bool UCraftingComponent::HasIngredients(AActor* Crafter, UDataDefinitionBase* InRecipe) const
{
    if (Crafter && UCraftingRecipeDataFunctionLibrary::HasCraftingRecipeData(InRecipe))
    {
        if (auto Inventory = Crafter->GetComponentByClass<UInventoryComponent>())
        {
            const TArray<FItem> Ingredients = UCraftingRecipeDataFunctionLibrary::GetIngredients(InRecipe);

            TArray<UDataInstanceBase*> IngredientItemInstances;
            IngredientItemInstances.Reserve(Ingredients.Num());
            for (const auto& Item : Ingredients)
            {
                const auto Definition = Item.Definition;
                const int32 Quantity = Item.Quantity;

                if (Quantity > 0)
                {
                    if (auto NewItemInstance = UItemDataFunctionLibrary::CreateItemInstance(Definition))
                    {
                        UItemDataFunctionLibrary::SetQuantity(NewItemInstance, Quantity);

                        IngredientItemInstances.Emplace(NewItemInstance);
                    }
                }
            }

            bool bHasIngredients = true;
            for (auto ItemInstance : IngredientItemInstances)
            {
                if (!Inventory->HasContent(ItemInstance))
                {
                    bHasIngredients = false;
                    break;
                }
            }

            return bHasIngredients;
        }
    }

    return false;
}

void UCraftingComponent::RemoveIngredients(AActor* Crafter, UDataDefinitionBase* InRecipe) const
{
    if (Crafter && UCraftingRecipeDataFunctionLibrary::HasCraftingRecipeData(InRecipe))
    {
        const TArray<FItem> Ingredients = UCraftingRecipeDataFunctionLibrary::GetIngredients(InRecipe);
        auto Inventory = Crafter->GetComponentByClass<UInventoryComponent>();

        TArray<UDataInstanceBase*> IngredientItemInstances;
        IngredientItemInstances.Reserve(Ingredients.Num());
        for (const auto& Item : Ingredients)
        {
            const auto Definition = Item.Definition;
            const int32 Quantity = Item.Quantity;

            if (Quantity > 0)
            {
                if (auto NewItemInstance = UItemDataFunctionLibrary::CreateItemInstance(Definition))
                {
                    UItemDataFunctionLibrary::SetQuantity(NewItemInstance, Quantity);

                    IngredientItemInstances.Emplace(NewItemInstance);
                }
            }
        }

        for (auto ItemInstance : IngredientItemInstances)
        {
            Inventory->RemoveContent(ItemInstance);
        }
    }
}

void UCraftingComponent::AddResults(AActor* Crafter, UDataDefinitionBase* InRecipe) const
{
    if (Crafter && UCraftingRecipeDataFunctionLibrary::HasCraftingRecipeData(InRecipe))
    {
        const TArray<FItem> Results = UCraftingRecipeDataFunctionLibrary::GetResults(InRecipe);
        auto Inventory = Crafter->GetComponentByClass<UInventoryComponent>();

        TArray<UDataInstanceBase*> ResultItemInstances;
        ResultItemInstances.Reserve(Results.Num());
        for (const auto& Item : Results)
        {
            const auto Definition = Item.Definition;
            const int32 Quantity = Item.Quantity;

            if (Quantity > 0)
            {
                if (auto NewItemInstance = UItemDataFunctionLibrary::CreateItemInstance(Definition))
                {
                    UItemDataFunctionLibrary::SetQuantity(NewItemInstance, Quantity);

                    ResultItemInstances.Emplace(NewItemInstance);
                }
            }
        }

        for (auto ItemInstance : ResultItemInstances)
        {
            Inventory->AddContent(ItemInstance);
        }
    }
}

void UCraftingComponent::OnCraftingFinished(AActor* Crafter, UDataDefinitionBase* InRecipe)
{
    if (!HasIngredients(Crafter, InRecipe)) return;

    RemoveIngredients(Crafter, InRecipe);
    AddResults(Crafter, InRecipe);
}
