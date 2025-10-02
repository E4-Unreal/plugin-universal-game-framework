// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/ShopListViewEntryWidget.h"

#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Data/DataDefinitionBase.h"
#include "FunctionLibraries/ProductDataFunctionLibrary.h"
#include "FunctionLibraries/SlotDataFunctionLibrary.h"

void UShopListViewEntryWidget::NativeOnListItemObjectSet(UObject* ListItemObject)
{
    Product = Cast<UDataDefinitionBase>(ListItemObject);

    Refresh();
}

void UShopListViewEntryWidget::Refresh()
{
    if (DisplayNameTextBlock)
    {
        DisplayNameTextBlock->SetText(Product->DisplayName);
    }

    if (ThumbnailImage)
    {
        ThumbnailImage->SetBrushFromSoftTexture(USlotDataFunctionLibrary::GetThumbnailTexture(Product));
    }

    if (BuyPriceTextBlock)
    {
        const int32 BuyPrice = UProductDataFunctionLibrary::GetBuyPrice(Product);
        BuyPriceTextBlock->SetText(FText::FromString(FString::FromInt(BuyPrice)));
    }
}
