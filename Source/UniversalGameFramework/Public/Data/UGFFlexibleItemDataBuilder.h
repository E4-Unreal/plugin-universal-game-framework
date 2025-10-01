// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Data/DataDefinitionBuilder.h"
#include "UGFFlexibleItemDataBuilder.generated.h"

/**
 *
 */
UCLASS()
class UNIVERSALGAMEFRAMEWORK_API UUGFFlexibleItemDataBuilder : public UDataDefinitionBuilder
{
    GENERATED_BODY()

public:
    UUGFFlexibleItemDataBuilder();

protected:

    /* DataDefinitionBuilder */

    virtual bool OnUpdateData(UDataDefinitionBase* Definition, FDataDefinitionTableRowBase* DataDefinitionTableRow) override;
};
