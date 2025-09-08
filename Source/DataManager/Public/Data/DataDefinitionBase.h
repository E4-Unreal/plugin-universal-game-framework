// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Interfaces/DataDefinitionInterface.h"
#include "DataDefinitionBase.generated.h"

/**
 *
 */
UCLASS(Abstract)
class DATAMANAGER_API UDataDefinitionBase : public UPrimaryDataAsset, public IDataDefinitionInterface
{
    GENERATED_BODY()

protected:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config", meta = (MustImplement = "DataInstanceInterface"))
    TArray<TSubclassOf<UObject>> InstanceClasses;

public:
    /* DataDefinitionInterface */

    virtual TArray<TSubclassOf<UObject>> GetInstanceClasses_Implementation() const override { return InstanceClasses; }
};
