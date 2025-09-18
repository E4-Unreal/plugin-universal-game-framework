// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Objects/DataAssetBuilder.h"
#include "UGFItemDefinitionBuilder.generated.h"

/**
 *
 */
UCLASS()
class UNIVERSALGAMEFRAMEWORK_API UUGFItemDefinitionBuilder : public UDataAssetBuilder
{
    GENERATED_BODY()

public:
    UUGFItemDefinitionBuilder();

    /* DataAssetBuilder */

    virtual bool UpdateData(UDataAsset* Data, FTableRowBase* TableRow) override;
};
