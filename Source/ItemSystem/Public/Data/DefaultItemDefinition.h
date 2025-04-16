// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ItemDefinition.h"
#include "DefaultItemDefinition.generated.h"

struct FDefaultItemDataTableRow;
/**
 *
 */
UCLASS()
class ITEMSYSTEM_API UDefaultItemDefinition : public UItemDefinition
{
    GENERATED_BODY()

protected:
    virtual void UpdateDataList(UScriptStruct* RowStruct, FTableRowBase* TableRow) override;
    void UpdateDataList(const FDefaultItemDataTableRow& DefaultItemDataTableRow);
};
