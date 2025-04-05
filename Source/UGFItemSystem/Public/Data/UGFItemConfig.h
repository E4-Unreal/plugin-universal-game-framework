// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "UGFItemConfig.generated.h"

/**
 *
 */
UCLASS(Abstract, Blueprintable, Const, DefaultToInstanced, EditInlineNew, CollapseCategories)
class UGFITEMSYSTEM_API UUGFItemConfig : public UPrimaryDataAsset
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintPure)
    virtual FORCEINLINE bool IsValid() const { return true; }
};
