// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/ShopListViewEntryWidget.h"

#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Data/DataDefinitionBase.h"
#include "FunctionLibraries/DataManagerFunctionLibrary.h"
#include "FunctionLibraries/ProductDataFunctionLibrary.h"
#include "FunctionLibraries/SlotDataFunctionLibrary.h"

void UShopListViewEntryWidget::NativeOnListItemObjectSet(UObject* ListItemObject)
{
    Product = ListItemObject;

    Refresh();
}

void UShopListViewEntryWidget::Refresh()
{
    if (auto Definition = Cast<UDataDefinitionBase>(Product.GetObject()))
    {
        if (DisplayNameTextBlock)
        {
            DisplayNameTextBlock->SetText(UDataManagerFunctionLibrary::GetDisplayName(Product.GetObject()));
        }

        if (ThumbnailImage)
        {
            ThumbnailImage->SetBrushFromSoftTexture(USlotDataFunctionLibrary::GetThumbnailTexture(Definition));
        }

        if (BuyPriceTextBlock)
        {
            const int32 BuyPrice = UProductDataFunctionLibrary::GetBuyPrice(Definition);
            BuyPriceTextBlock->SetText(FText::FromString(FString::FromInt(BuyPrice)));
        }
    }
}
