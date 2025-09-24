// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Data/DataObjectBase.h"
#include "FlexibleDataObjectBase.generated.h"

class UDataObjectFragment;

/**
 *
 */
UCLASS(Abstract)
class DATAMANAGER_API UFlexibleDataObjectBase : public UDataObjectBase
{
    GENERATED_BODY()

public:
    /* API */

    UFUNCTION(BlueprintPure)
    virtual UDataObjectFragment* GetFragmentByInterface(const TSubclassOf<UInterface> InterfaceClass) const { return nullptr; }
};
