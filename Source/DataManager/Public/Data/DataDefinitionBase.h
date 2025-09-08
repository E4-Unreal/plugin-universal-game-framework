// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "DataDefinitionBase.generated.h"

class UDataInstanceBase;
class UDataInstanceContainer;

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
    UDataInstanceContainer* CreateCollection() const;

    UFUNCTION(BlueprintCallable)
    virtual TArray<UObject*> CreateInstances() const;

    UFUNCTION(BlueprintPure)
    bool CanCreateInstance(TSubclassOf<UDataInstanceBase> InstanceClass) const;

    UFUNCTION(BlueprintCallable)
    UObject* CreateInstance(TSubclassOf<UDataInstanceBase> InstanceClass) const;
};
