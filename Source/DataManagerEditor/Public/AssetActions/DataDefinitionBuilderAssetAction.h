// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AssetActionUtility.h"
#include "DataDefinitionBuilderAssetAction.generated.h"

class UDataDefinitionBuilder;
class UDataDefinitionBase;

/**
 * DataAssetBuilder 클래스에 정의된 방식으로 데이터 테이블로부터 데이터 에셋을 생성하는 에셋 액션
 */
UCLASS()
class DATAMANAGEREDITOR_API UDataDefinitionBuilderAssetAction : public UAssetActionUtility
{
    GENERATED_BODY()

public:
    UDataDefinitionBuilderAssetAction();

    UFUNCTION(CallInEditor)
    void Build();

protected:
    virtual void BuildData(UDataDefinitionBuilder* Builder) const;
    static UDataDefinitionBase* CreateData(UDataDefinitionBuilder* Builder, int32 ID);
    static void UpdatePackageName(UDataDefinitionBase* Definition, UDataDefinitionBuilder* Builder, int32 ID);

    static UDataDefinitionBase* ChangeDataAssetClass(UDataDefinitionBase* OldDefinition, TSubclassOf<UDataDefinitionBase> NewDefinitionClass);
};
