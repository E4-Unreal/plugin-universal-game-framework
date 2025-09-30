// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "DataFragment.generated.h"

class UDataInstanceFragment;

/**
 *
 */
UCLASS(Abstract, EditInlineNew, CollapseCategories)
class DATAMANAGER_API UDataFragment : public UPrimaryDataAsset
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintPure)
    virtual UDataInstanceFragment* CreateDataInstanceFragment() const { return nullptr; }
};
