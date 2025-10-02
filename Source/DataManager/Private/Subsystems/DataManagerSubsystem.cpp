// Fill out your copyright notice in the Description page of Project Settings.


#include "Subsystems/DataManagerSubsystem.h"

#include "Engine/AssetManager.h"

bool UDataManagerSubsystem::ShouldCreateSubsystem(UObject* Outer) const
{
    TArray<UClass*> ChildClasses;
    GetDerivedClasses(GetClass(), ChildClasses, false);

    return ChildClasses.Num() == 0;
}

TSoftObjectPtr<UDataAsset> UDataManagerSubsystem::GetDataAsset(FName AssetType, int32 ID) const
{
    FPrimaryAssetId AssetID = FPrimaryAssetId(AssetType, FName(FString::FromInt(ID)));
    FAssetData AssetData;
    UAssetManager::Get().GetPrimaryAssetData(AssetID, AssetData);

    return TSoftObjectPtr<UDataAsset>(AssetData.GetSoftObjectPath());
}

TArray<TSoftObjectPtr<UDataAsset>> UDataManagerSubsystem::GetDataAssets(FName AssetType) const
{
    TArray<FAssetData> AssetDataList;
    UAssetManager::Get().GetPrimaryAssetDataList(AssetType, AssetDataList);

    TArray<TSoftObjectPtr<UDataAsset>> DataAssets;
    DataAssets.Reserve(AssetDataList.Num());
    for (const auto& AssetData : AssetDataList)
    {
        TSoftObjectPtr<UDataAsset> DataAsset = TSoftObjectPtr<UDataAsset>(AssetData.GetSoftObjectPath());
        if (!DataAsset.IsNull())
        {
            DataAssets.Emplace(DataAsset);
        }
    }

    return DataAssets;
}

TMap<int32, TSoftObjectPtr<UDataAsset>> UDataManagerSubsystem::GetDataAssetMap(FName AssetType) const
{
    TArray<TSoftObjectPtr<UDataAsset>> DataAssets = GetDataAssets(AssetType);

    TMap<int32, TSoftObjectPtr<UDataAsset>> DataAssetMap;
    DataAssetMap.Reserve(DataAssets.Num());
    for (TSoftObjectPtr<UDataAsset> DataAsset : DataAssets)
    {
        if (!DataAsset.IsNull())
        {
            FString IDString = UAssetManager::Get().GetPrimaryAssetIdForPath(DataAsset.ToSoftObjectPath()).PrimaryAssetName.ToString();
            if (IDString.IsNumeric())
            {
                const int32 ID = FCString::Atoi(*IDString);
                DataAssetMap.Emplace(ID, DataAsset);
            }
        }
    }

    return DataAssetMap;
}
