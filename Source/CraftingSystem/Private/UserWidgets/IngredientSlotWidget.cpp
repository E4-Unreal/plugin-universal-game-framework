// Fill out your copyright notice in the Description page of Project Settings.


#include "UserWidgets/IngredientSlotWidget.h"

#include "Components/Image.h"
#include "Components/InventoryComponent.h"
#include "Components/TextBlock.h"
#include "Data/DataInstanceBase.h"
#include "FunctionLibraries/ItemDataFunctionLibrary.h"
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

void UIngredientSlotWidget::SetDataObject_Implementation(UObject* NewDataObject)
{
    if (auto NewItemInstance = Cast<UDataInstanceBase>(NewDataObject))
    {
        FItem NewItem;
        NewItem.Definition = NewItemInstance->GetDefinition();
        NewItem.Quantity = UItemDataFunctionLibrary::GetQuantity(NewItemInstance);

        SetItem(NewItem);
    }
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
    NewOwnedQuantity = FMath::Max(0, NewOwnedQuantity);

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
