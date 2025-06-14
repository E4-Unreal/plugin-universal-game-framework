// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/ShopListViewPanelWidget.h"

#include "Components/ListView.h"

void UShopListViewPanelWidget::SetProducts(const TArray<TScriptInterface<IProductInterface>>& NewProducts)
{
    Products = NewProducts;

    Refresh();
}

void UShopListViewPanelWidget::NativePreConstruct()
{
    Super::NativePreConstruct();

    Refresh();
}

void UShopListViewPanelWidget::Refresh()
{
    if (ShopListView && ShopListView->GetDefaultEntryClass())
    {
        const auto& TargetProducts = Products.IsEmpty() ? PreviewProducts : Products;
        for (const auto& TargetProduct : TargetProducts)
        {
            ShopListView->AddItem(TargetProduct.GetObject());
        }
    }
}
