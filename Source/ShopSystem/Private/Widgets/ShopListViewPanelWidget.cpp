// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/ShopListViewPanelWidget.h"

#include "Components/ListView.h"
#include "Data/DataDefinitionBase.h"
#include "Widgets/BuyModalWidget.h"

void UShopListViewPanelWidget::NativeOnInitialized()
{
    Super::NativeOnInitialized();

    SetProducts(DefaultProducts);

    if (ShopListView)
    {
        auto& ItemDoubleClickedDelegate = ShopListView->OnItemDoubleClicked();
        ItemDoubleClickedDelegate.AddUObject(this, &ThisClass::OnItemDoubleClicked);
    }
}

void UShopListViewPanelWidget::OnItemDoubleClicked(UObject* Item)
{
    // 구매 팝업 창 표시
    if (BuyModalWidgetClass)
    {
        auto BuyModalWidget = CreateWidget<UBuyModalWidget>(this, BuyModalWidgetClass);
        BuyModalWidget->SetProduct(Item);
        BuyModalWidget->AddToViewport();
    }
}

void UShopListViewPanelWidget::SetProducts(const TArray<UDataDefinitionBase*>& NewProducts)
{
    Products = NewProducts;

    if (ShopListView && ShopListView->GetDefaultEntryClass())
    {
        ShopListView->ClearListItems();
        for (const auto& Product : Products)
        {
            ShopListView->AddItem(Product);
        }
    }
}
