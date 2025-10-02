// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FlexibleDataDefinitionBase.h"
#include "FlexibleDataDefinition.generated.h"

/**
 *
 */
UCLASS()
class DATAMANAGER_API UFlexibleDataDefinition : public UFlexibleDataDefinitionBase
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config", Instanced)
    TArray<TObjectPtr<UDataFragment>> Fragments;

public:
    /* FlexibleDataBase */

    virtual const TArray<UDataFragment*>& GetFragments() const override { return Fragments; }

    /* API */

    UFUNCTION(BlueprintCallable)
    UDataFragment* AddFragment(TSubclassOf<UDataFragment> FragmentClass);

    template <typename TFragment = UDataFragment>
    TFragment* AddFragment()
    {
        return Cast<TFragment>(AddFragment(TFragment::StaticClass()));
    }
};
