// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ItemData.generated.h"

/**
 * ItemDefinition::DataList 전용 구조체로 필요에 따라 커스텀 ItemData 구조체 작성이 필요합니다.
 * ActorItemData 참조
 */
USTRUCT(Atomic, BlueprintType)
struct FItemData : public FTableRowBase
{
    GENERATED_BODY()
};
