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

protected:
    static const TArray<UDataFragment*> EmptyFragments;

public:
    UFlexibleDataBase();

    /* DataInterface */

    virtual UDataAsset* GetDataByInterface_Implementation(TSubclassOf<UInterface> InterfaceClass) const override;
    virtual UObject* CreateInstanceData_Implementation() const override;

    /* API */

    UFUNCTION(BlueprintPure)
    virtual const TArray<UDataFragment*>& GetFragments() const;

    UFUNCTION(BlueprintPure)
    UDataFragment* CreateFragment(TSubclassOf<UDataFragment> FragmentClass) const;

    template <typename TFragment = UDataFragment>
    TFragment* CreateFragment() const
    {
        return Cast<TFragment>(CreateFragment(TFragment::StaticClass()));
    }

    UFUNCTION(BlueprintPure)
    UDataFragment* GetFragmentByClass(TSubclassOf<UDataFragment> FragmentClass) const;

    template <typename TFragment = UDataFragment>
    TFragment* GetFragmentByClass() const
    {
        return Cast<TFragment>(GetFragmentByClass(TFragment::StaticClass()));
    }

    UFUNCTION(BlueprintPure)
    UDataFragment* GetFragmentByInterface(const TSubclassOf<UInterface> InterfaceClass) const;

    template <typename TInterface = UInterface>
    UDataFragment* GetFragmentByInterface() const
    {
        return GetFragmentByInterface(TInterface::StaticClass());
    }
};
