// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "DataDefinitionBase.generated.h"

class UDataInstanceContainer;
class UObject;

/**
 *
 */
UCLASS(Abstract)
class DATAMANAGER_API UDataDefinitionBase : public UPrimaryDataAsset
{
    GENERATED_BODY()

protected:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
    TArray<TSubclassOf<UObject>> InstanceClasses;

public:
    UFUNCTION(BlueprintCallable)
    UDataInstanceContainer* CreateCollection() const;

    UFUNCTION(BlueprintCallable)
    virtual TArray<UObject*> CreateInstances() const;

    UFUNCTION(BlueprintPure)
    virtual bool CanCreateInstance(TSubclassOf<UObject> InstanceClass) const;

    UFUNCTION(BlueprintCallable)
    virtual UObject* CreateInstance(TSubclassOf<UObject> InstanceClass) const;
};
