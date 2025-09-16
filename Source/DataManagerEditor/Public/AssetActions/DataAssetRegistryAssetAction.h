// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Editor/Blutility/Classes/AssetActionUtility.h"
#include "DataAssetRegistryAssetAction.generated.h"

class UDataAssetRegistry;

/**
 * DataAssetRegistry에 설정된 DataTable과 DataAssetBuilder 클래스를 기반으로 데이터 에셋을 생성하고 생성된 데이터 에셋 매핑 정보를 DataAssetRegistry에 설정하는 에셋 액션
 */
UCLASS()
class DATAMANAGEREDITOR_API UDataAssetRegistryAssetAction : public UAssetActionUtility
{
    GENERATED_BODY()

public:
    UDataAssetRegistryAssetAction();

    UFUNCTION(CallInEditor)
    void Build();

protected:
    virtual void BuildData(UDataAssetRegistry* DataAssetRegistry) const;
    static TSet<int32> GetIDSet(UDataTable* DataTable);
    static int32 ConvertRowNameToID(FName RowName);
    static UDataAsset* CreateData(TSubclassOf<UDataAsset> DataClass, int32 ID, FString AssetPath);
};
