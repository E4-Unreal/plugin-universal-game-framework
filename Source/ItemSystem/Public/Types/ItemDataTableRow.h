// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine/DataTable.h"
#include "ItemDataTableRow.generated.h"

/**
 * 프로젝트 전용 ItemDataTableRow 구조체 작성이 필요합니다.
 * DefaultItemDataTableRow 참조
 */
USTRUCT(Atomic, BlueprintType)
struct FItemDataTableRow : public FTableRowBase
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FText DisplayText;
};
