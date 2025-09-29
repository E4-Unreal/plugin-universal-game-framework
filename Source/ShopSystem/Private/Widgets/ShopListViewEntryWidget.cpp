// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/ShopListViewEntryWidget.h"

#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "FunctionLibraries/DataManagerFunctionLibrary.h"
#include "FunctionLibraries/ShopSystemFunctionLibrary.h"
#include "FunctionLibraries/SlotManagerFunctionLibrary.h"

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
        DisplayNameTextBlock->SetText(UDataManagerFunctionLibrary::GetDisplayName(Product.GetObject()));
    }

    if (ThumbnailImage)
    {
        ThumbnailImage->SetBrushFromSoftTexture(USlotManagerFunctionLibrary::GetThumbnailTexture(Product.GetObject()));
    }

    if (BuyPriceTextBlock)
    {
        const int32 BuyPrice = UShopSystemFunctionLibrary::GetBuyPrice(Product.GetObject());
        BuyPriceTextBlock->SetText(FText::FromString(FString::FromInt(BuyPrice)));
    }
}
