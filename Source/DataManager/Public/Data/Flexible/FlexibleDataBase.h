// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Data/DataDefinitionBase.h"
#include "FlexibleDataBase.generated.h"

class UDataFragment;

/**
 *
 */
UCLASS(Abstract)
class DATAMANAGER_API UFlexibleDataBase : public UDataDefinitionBase
{
    GENERATED_BODY()

public:
    /* API */

    UFUNCTION(BlueprintPure)
    virtual UDataFragment* GetFragmentByInterface(const TSubclassOf<UInterface> InterfaceClass) const { return nullptr; }
};
