// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/ShopListViewEntryWidget.h"

#include "Components/Image.h"
#include "Components/ShopComponent.h"
#include "Components/TextBlock.h"
#include "Data/DataDefinitionBase.h"
#include "FunctionLibraries/ProductDataFunctionLibrary.h"
#include "FunctionLibraries/SlotDataFunctionLibrary.h"

UShopListViewEntryWidget::UShopListViewEntryWidget(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer)
{
    SetVisibilityInternal(ESlateVisibility::Visible);

    StockTextFormat = NSLOCTEXT("ShopSystem", "StockTextFormat", "{0} / {1}");
}

void UShopListViewEntryWidget::NativeOnListItemObjectSet(UObject* ListItemObject)
{
    Refresh();
}

void UShopListViewEntryWidget::Refresh()
{
    if (auto ProductSlotContainer = GetListItem<UProductSlotContainer>())
    {
        const auto& ProductSlot = ProductSlotContainer->Slot;
        auto Item = ProductSlot.Definition;
        const int32 Stock = ProductSlot.Stock;
        const int32 MaxStock = ProductSlot.MaxStock;
        const bool bInfiniteStock = ProductSlot.bInfiniteStock;

        if (DisplayNameTextBlock)
        {
            DisplayNameTextBlock->SetText(Item->DisplayName);
        }

        if (ThumbnailImage)
        {
            ThumbnailImage->SetBrushFromSoftTexture(USlotDataFunctionLibrary::GetThumbnailTexture(Item));
        }

        if (BuyPriceTextBlock)
        {
            const int32 BuyPrice = UProductDataFunctionLibrary::GetBuyPrice(Item);
            BuyPriceTextBlock->SetText(FText::AsNumber(BuyPrice));
        }

        if (StockTextBlock)
        {
            FText StockText = bInfiniteStock ? FText::FromString("∞") : FText::FromString(FString::FromInt(Stock));
            FText MaxStockText = bInfiniteStock ? FText::FromString("∞") : FText::FromString(FString::FromInt(MaxStock));

            StockTextBlock->SetText(FText::Format(StockTextFormat, StockText, MaxStockText));
        }
    }
}
