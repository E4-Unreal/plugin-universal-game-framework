// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/EngineSubsystem.h"
#include "DataManagerSubsystem.generated.h"

/**
 *
 */
UCLASS()
class DATAMANAGER_API UDataManagerSubsystem : public UEngineSubsystem
{
    GENERATED_BODY()

public:
    /* Subsystem */

    virtual bool ShouldCreateSubsystem(UObject* Outer) const override;

    /* API */

    UFUNCTION(BlueprintPure)
    virtual TSoftObjectPtr<UDataAsset> GetDataAsset(FName AssetType, int32 ID) const;

    template <typename TDataAssetClass = UDataAsset>
    TSoftObjectPtr<TDataAssetClass> GetDataAsset(FName AssetType, int32 ID) const
    {
        return TSoftObjectPtr<TDataAssetClass>(GetDataAsset(AssetType, ID).ToSoftObjectPath());
    }

    UFUNCTION(BlueprintPure)
    virtual TArray<TSoftObjectPtr<UDataAsset>> GetDataAssets(FName AssetType) const;

    template <typename TDataAssetClass = UDataAsset>
    TArray<TSoftObjectPtr<TDataAssetClass>> GetDataAssets(FName AssetType) const
    {
        TArray<TSoftObjectPtr<UDataAsset>> DataAssets = GetDataAssets(AssetType);
        TArray<TSoftObjectPtr<TDataAssetClass>> CastedDataAssets;
        CastedDataAssets.Reserve(DataAssets.Num());

        for (auto DataAsset : DataAssets)
        {
            if (auto CastedDataAsset = TSoftObjectPtr<TDataAssetClass>(DataAsset.ToSoftObjectPath()))
            {
                CastedDataAssets.Emplace(CastedDataAsset);
            }
        }

        return CastedDataAssets;
    }

    UFUNCTION(BlueprintPure)
    virtual TMap<int32, TSoftObjectPtr<UDataAsset>> GetDataAssetMap(FName AssetType) const;

    template <typename TDataAssetClass = UDataAsset>
    TMap<int32, TSoftObjectPtr<TDataAssetClass>> GetDataAssetMap(FName AssetType) const
    {
        TMap<int32, TSoftObjectPtr<UDataAsset>> DataAssetMap = GetDataAssetMap(AssetType);
        TMap<int32, TSoftObjectPtr<TDataAssetClass>> CastedDataAssetMap;
        CastedDataAssetMap.Reserve(DataAssetMap.Num());

        for (const auto& [ID, DataAsset] : DataAssetMap)
        {
            if (auto CastedDataAsset = TSoftObjectPtr<TDataAssetClass>(DataAsset.ToSoftObjectPath()))
            {
                CastedDataAssetMap.Emplace(ID, CastedDataAsset);
            }
        }

        return CastedDataAssetMap;
    }
};
