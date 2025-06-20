// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/ShopListViewPanelWidget.h"

#include "Components/ListView.h"

void UShopListViewPanelWidget::NativeOnInitialized()
{
    Super::NativeOnInitialized();

    SetProducts(DefaultProducts);
}

void UShopListViewPanelWidget::SetProducts(const TArray<TScriptInterface<IProductInterface>>& NewProducts)
{
    Products = NewProducts;

    if (ShopListView && ShopListView->GetDefaultEntryClass())
    {
        ShopListView->ClearListItems();
        for (const auto& Product : Products)
        {
            ShopListView->AddItem(Product.GetObject());
        }
    }
}
