// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AssetActionUtility.h"
#include "DataAssetBuilderAssetAction.generated.h"

class UDataAssetBuilder;

/**
 * DataAssetBuilder 클래스에 정의된 방식으로 데이터 테이블로부터 데이터 에셋을 생성하는 에셋 액션
 */
UCLASS()
class DATAMANAGEREDITOR_API UDataAssetBuilderAssetAction : public UAssetActionUtility
{
    GENERATED_BODY()

public:
    UDataAssetBuilderAssetAction();

    UFUNCTION(CallInEditor)
    void Build();

protected:
    virtual void BuildData(UDataAssetBuilder* Builder) const;
    static TSet<int32> GetIDSet(UDataTable* DataTable);
    static int32 ConvertRowNameToID(FName RowName);
    static UDataAsset* CreateData(UDataAssetBuilder* Builder, int32 ID);
    static FTableRowBase* GetTableRow(UDataTable* DataTable, int32 ID);
    static void UpdatePackageName(UDataAsset* DataAsset, UDataAssetBuilder* Builder);
};
