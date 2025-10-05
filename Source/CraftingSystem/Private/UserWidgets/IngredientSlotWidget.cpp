// Fill out your copyright notice in the Description page of Project Settings.


#include "UserWidgets/IngredientSlotWidget.h"

#include "Components/Image.h"
#include "Components/InventoryComponent.h"
#include "Components/TextBlock.h"
#include "FunctionLibraries/SlotDataFunctionLibrary.h"

void UIngredientSlotWidget::SynchronizeProperties()
{
    Super::SynchronizeProperties();

#if WITH_EDITOR
    if (IsDesignTime())
    {
        if (PreviewItem.Definition)
        {
            SetItem(PreviewItem);
        }
    }
#endif
}

void UIngredientSlotWidget::SetItem_Implementation(UObject* NewItem)
{
    // TODO FItem
}

void UIngredientSlotWidget::SetThumbnailTexture(TSoftObjectPtr<UTexture2D> NewThumbnailTexture)
{
    if (GetThumbnailImage())
    {
        if (NewThumbnailTexture.IsNull())
        {
            GetThumbnailImage()->SetBrushTintColor(FSlateColor(FLinearColor::Transparent));
        }
        else
        {
            GetThumbnailImage()->SetBrushTintColor(FSlateColor(FLinearColor::White));
            GetThumbnailImage()->SetBrushFromSoftTexture(NewThumbnailTexture);
        }
    }
}

void UIngredientSlotWidget::SetOwnedQuantity(int32 NewOwnedQuantity)
{
    NewOwnedQuantity = FMath::Min(0, NewOwnedQuantity);

    if (GetOwnedQuantityTextBlock())
    {
        GetOwnedQuantityTextBlock()->SetText(FText::FromString(FString::FromInt(NewOwnedQuantity)));
    }
}

void UIngredientSlotWidget::SetNeededQuantity(int32 NewNeededQuantity)
{
    NewNeededQuantity = FMath::Max(0, NewNeededQuantity);

    if (GetNeededQuantityTextBlock())
    {
        GetNeededQuantityTextBlock()->SetText(FText::FromString(FString::FromInt(NewNeededQuantity)));
    }
}

void UIngredientSlotWidget::SetItem(const FItem& NewItem)
{
    auto ItemDefinition = NewItem.Definition;
    auto ThumbnailTexture = USlotDataFunctionLibrary::GetThumbnailTexture(ItemDefinition);
    const int32 Quantity = NewItem.Quantity;
    int32 OwnedQuantity = 0;
    if (auto OwningPlayerPawn = GetOwningPlayerPawn())
    {
        if (auto Inventory = OwningPlayerPawn->GetComponentByClass<UInventoryComponent>())
        {
            OwnedQuantity = Inventory->GetItemQuantity(ItemDefinition);
        }
    }

    SetThumbnailTexture(ThumbnailTexture);
    SetOwnedQuantity(OwnedQuantity);
    SetNeededQuantity(Quantity);
}
