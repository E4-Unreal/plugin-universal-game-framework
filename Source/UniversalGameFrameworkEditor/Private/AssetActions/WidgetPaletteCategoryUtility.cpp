// Fill out your copyright notice in the Description page of Project Settings.


#include "AssetActions/WidgetPaletteCategoryUtility.h"

#include "AssetSelection.h"
#include "Engine/Blueprint.h"
#include "Blueprint/UserWidget.h"

UWidgetPaletteCategoryUtility::UWidgetPaletteCategoryUtility()
{
    bIsActionForBlueprints = true;
    SupportedClasses.Emplace(UUserWidget::StaticClass());
}

void UWidgetPaletteCategoryUtility::SetPaletteCategory(FString NewCategory)
{
    TArray<FAssetData> SelectedAssets;
    AssetSelectionUtils::GetSelectedAssets(SelectedAssets);
    for (const auto& SelectedAsset : SelectedAssets)
    {
        if (UUserWidget* Widget = GetUserWidget(SelectedAsset))
        {
            if (Widget->PaletteCategory.ToString() != NewCategory)
            {
                Widget->PaletteCategory = FText::FromString(NewCategory);
                Widget->MarkPackageDirty();
            }
        }
    }
}

UUserWidget* UWidgetPaletteCategoryUtility::GetUserWidget(const FAssetData& AssetData)
{
    if (UBlueprint* Blueprint = Cast<UBlueprint>(AssetData.GetAsset()))
    {
        if (UClass* GeneratedClass = Blueprint->GeneratedClass)
        {
            if (GeneratedClass->IsChildOf(UUserWidget::StaticClass()))
            {
                return GeneratedClass->GetDefaultObject<UUserWidget>();
            }
        }
    }

    return nullptr;
}
