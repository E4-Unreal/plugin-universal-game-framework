// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Data/DataDefinitionBuilder.h"
#include "UGFItemDefinitionBuilder.generated.h"

/**
 *
 */
UCLASS()
class UNIVERSALGAMEFRAMEWORK_API UUGFItemDefinitionBuilder : public UDataDefinitionBuilder
{
    GENERATED_BODY()

public:
    UUGFItemDefinitionBuilder();

protected:

    /* DataDefinitionBuilder */

    virtual bool OnUpdateData(UDataDefinitionBase* Definition, FDataDefinitionTableRowBase* DataDefinitionTableRow) override;

};
