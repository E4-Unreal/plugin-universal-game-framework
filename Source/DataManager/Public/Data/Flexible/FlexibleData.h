// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FlexibleDataBase.h"
#include "FlexibleData.generated.h"

/**
 *
 */
UCLASS()
class DATAMANAGER_API UFlexibleData : public UFlexibleDataBase
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config", Instanced)
    TArray<TObjectPtr<UDataFragment>> Fragments;

public:
    /* FlexibleDataBase */

    virtual UDataFragment* GetFragmentByInterface(const TSubclassOf<UInterface> InterfaceClass) const override;
};
