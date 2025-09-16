// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Data/DataInstanceBase.h"
#include "FlexibleDataInstanceBase.generated.h"

class UDataInstanceFragment;

/**
 *
 */
UCLASS(Abstract)
class DATAMANAGER_API UFlexibleDataInstanceBase : public UDataInstanceBase
{
    GENERATED_BODY()

public:
    /* API */

    UFUNCTION(BlueprintPure)
    virtual UDataInstanceFragment* GetFragmentByInterface(const TSubclassOf<UInterface> InterfaceClass) const { return nullptr; }
};
