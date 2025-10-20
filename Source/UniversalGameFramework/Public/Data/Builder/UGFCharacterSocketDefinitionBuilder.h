// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Data/DataDefinitionBuilder.h"
#include "UGFCharacterSocketDefinitionBuilder.generated.h"

/**
 *
 */
UCLASS()
class UNIVERSALGAMEFRAMEWORK_API UUGFCharacterSocketDefinitionBuilder : public UDataDefinitionBuilder
{
    GENERATED_BODY()

public:
    UUGFCharacterSocketDefinitionBuilder();

protected:
    /* DataDefinitionBuilder */

    virtual bool OnUpdateData(UDataDefinitionBase* Definition,
        FDataDefinitionTableRowBase* DataDefinitionTableRow) override;
};
