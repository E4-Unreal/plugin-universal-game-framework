// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Data/DataAssetBuilder.h"
#include "UGFFlexibleItemDataBuilder.generated.h"

/**
 *
 */
UCLASS()
class UNIVERSALGAMEFRAMEWORK_API UUGFFlexibleItemDataBuilder : public UDataAssetBuilder
{
    GENERATED_BODY()

public:
    UUGFFlexibleItemDataBuilder();

    /* DataAssetBuilder */

    virtual bool UpdateData(UDataAsset* Data, FTableRowBase* TableRow) override;
};
