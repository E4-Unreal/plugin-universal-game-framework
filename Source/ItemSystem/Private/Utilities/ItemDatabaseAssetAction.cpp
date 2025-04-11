// Fill out your copyright notice in the Description page of Project Settings.


#include "Utilities/ItemDatabaseAssetAction.h"

#include "AssetSelection.h"
#include "Data/ItemDatabase.h"

UItemDatabaseAssetAction::UItemDatabaseAssetAction()
{
    SupportedClasses.Emplace(UItemDatabase::StaticClass());
}

void UItemDatabaseAssetAction::HardUpdate()
{
    TArray<FAssetData> SelectedAssets;
    AssetSelectionUtils::GetSelectedAssets(SelectedAssets);

    for (const auto& SelectedAsset : SelectedAssets)
    {
        if (auto ItemDatabase = Cast<UItemDatabase>(SelectedAsset.GetAsset()))
        {
            ItemDatabase->HardUpdate();
        }
    }
}
