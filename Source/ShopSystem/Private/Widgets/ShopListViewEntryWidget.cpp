// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/ShopListViewEntryWidget.h"

#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Interfaces/ProductInterface.h"

void UShopListViewEntryWidget::NativeOnListItemObjectSet(UObject* ListItemObject)
{
    Product = ListItemObject;

    Refresh();
}

void UShopListViewEntryWidget::Refresh()
{
    if (!Product) return;

    if (DisplayNameTextBlock)
    {
        DisplayNameTextBlock->SetText(IProductInterface::Execute_GetDisplayNameText(Product.GetObject()));
    }

    if (ThumbnailImage)
    {
        ThumbnailImage->SetBrushFromSoftTexture(IProductInterface::Execute_GetThumbnailTexture(Product.GetObject()));
    }

    if (BuyPriceTextBlock)
    {
        BuyPriceTextBlock->SetText(FText::FromString(FString::FromInt(IProductInterface::Execute_GetBuyPrice(Product.GetObject()))));
    }
}
