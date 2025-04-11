// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AssetActionUtility.h"
#include "ItemDatabaseAssetAction.generated.h"

/**
 * ItemDatabase 데이터 에셋 전용 에셋 액션 유틸리티
 */
UCLASS()
class ITEMSYSTEM_API UItemDatabaseAssetAction : public UAssetActionUtility
{
    GENERATED_BODY()

public:
    UItemDatabaseAssetAction();

    UFUNCTION(CallInEditor)
    void HardUpdate();
};
