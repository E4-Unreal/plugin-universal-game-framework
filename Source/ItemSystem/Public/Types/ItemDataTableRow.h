// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine/DataTable.h"
#include "ItemDataTableRow.generated.h"

/**
 * 아이템 데이터 테이블 전용 구조체
 */
USTRUCT(Atomic, BlueprintType)
struct FItemDataTableRow : public FTableRowBase
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FText DisplayText;
};
