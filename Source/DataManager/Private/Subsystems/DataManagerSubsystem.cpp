// Fill out your copyright notice in the Description page of Project Settings.


#include "Subsystems/DataManagerSubsystem.h"

#include "Engine/AssetManager.h"
#include "Interfaces/DataInterface.h"

bool UDataManagerSubsystem::ShouldCreateSubsystem(UObject* Outer) const
{
    TArray<UClass*> ChildClasses;
    GetDerivedClasses(GetClass(), ChildClasses, false);

    return ChildClasses.Num() == 0;
}

UDataAsset* UDataManagerSubsystem::GetDataAsset(FName AssetType, int32 ID) const
{
    FPrimaryAssetId AssetID = FPrimaryAssetId(AssetType, FName(FString::FromInt(ID)));

    return UAssetManager::Get().GetPrimaryAssetObject<UDataAsset>(AssetID);
}

TArray<UDataAsset*> UDataManagerSubsystem::GetDataAssets(FName AssetType) const
{
    TArray<UObject*> Objects;
    UAssetManager::Get().GetPrimaryAssetObjectList(AssetType, Objects);

    TArray<UDataAsset*> DataAssets;
    DataAssets.Reserve(Objects.Num());
    for (UObject* Object : Objects)
    {
        if (UDataAsset* DataAsset = Cast<UDataAsset>(Object))
        {
            DataAssets.Emplace(DataAsset);
        }
    }

    return DataAssets;
}

TMap<int32, UDataAsset*> UDataManagerSubsystem::GetDataAssetMap(FName AssetType) const
{
    TArray<UDataAsset*> DataAssets = GetDataAssets(AssetType);

    TMap<int32, UDataAsset*> DataAssetMap;
    DataAssetMap.Reserve(DataAssets.Num());
    for (UDataAsset* DataAsset : DataAssets)
    {
        if (DataAsset && DataAsset->Implements<UDataInterface>())
        {
            const int32 ID = IDataInterface::Execute_GetID(DataAsset);
            DataAssetMap.Emplace(ID, DataAsset);
        }
    }

    return DataAssetMap;
}
