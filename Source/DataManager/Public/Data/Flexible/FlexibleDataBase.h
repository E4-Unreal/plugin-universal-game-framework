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
    /* DataInterface */

    virtual bool SupportsInterface_Implementation(TSubclassOf<UInterface> InterfaceClass) const override;

    /* API */

    UFUNCTION(BlueprintPure)
    virtual UDataFragment* GetFragmentByClass(TSubclassOf<UDataFragment> FragmentClass) const { return nullptr; }

    template <typename TFragment = UDataFragment>
    TFragment* GetFragmentByClass() const
    {
        return GetFragmentByClass(TFragment::StaticClass());
    }

    UFUNCTION(BlueprintPure)
    virtual UDataFragment* GetFragmentByInterface(const TSubclassOf<UInterface> InterfaceClass) const { return nullptr; }

    template <typename TInterface = UInterface>
    UDataFragment* GetFragmentByInterface() const
    {
        return GetFragmentByInterface(TInterface::StaticClass());
    }
};
