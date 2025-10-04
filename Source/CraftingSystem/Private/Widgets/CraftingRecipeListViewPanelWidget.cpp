// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/CraftingRecipeListViewPanelWidget.h"

#include "Components/CraftingComponent.h"
#include "Components/ListView.h"
#include "Data/DataDefinitionBase.h"

UCraftingRecipeListViewPanelWidget::UCraftingRecipeListViewPanelWidget(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer)
{
    TargetComponentClass = UCraftingComponent::StaticClass();
}

void UCraftingRecipeListViewPanelWidget::Refresh_Implementation()
{
    Super::Refresh_Implementation();

    if (auto CraftingComponent = GetTargetComponent<UCraftingComponent>())
    {
        const auto& Recipes = CraftingComponent->GetRecipes();
        if (GetListView() && GetListView()->GetDefaultEntryClass())
        {
            for (auto Recipe : Recipes)
            {
                GetListView()->AddItem(Recipe);
            }
        }
    }
}

void UCraftingRecipeListViewPanelWidget::Clear_Implementation()
{
    Super::Clear_Implementation();

    if (GetListView())
    {
        GetListView()->ClearListItems();
    }
}
