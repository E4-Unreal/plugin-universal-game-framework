// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "DataDefinitionBase.generated.h"

class UDataCollection;
class UDataInstanceBase;

/**
 *
 */
UCLASS(Abstract)
class DATAMANAGER_API UDataDefinitionBase : public UPrimaryDataAsset
{
    GENERATED_BODY()

protected:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
    TArray<TSubclassOf<UDataInstanceBase>> InstanceClasses;

public:
    UFUNCTION(BlueprintCallable)
    UDataCollection* CreateCollection() const;

    UFUNCTION(BlueprintCallable)
    virtual TArray<UDataInstanceBase*> CreateInstances() const;

    UFUNCTION(BlueprintCallable)
    virtual UDataInstanceBase* CreateInstance(TSubclassOf<UDataInstanceBase> InstanceClass) const;
};
