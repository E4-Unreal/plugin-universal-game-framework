// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "DataActorInterface.generated.h"

UINTERFACE(MinimalAPI, Blueprintable, BlueprintType)
class UDataActorInterface : public UInterface
{
    GENERATED_BODY()
};

/**
 *
 */
class DATAMANAGER_API IDataActorInterface
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
    TArray<UObject*> GetDataInstances() const;

    UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
    void SetDataInstances(const TArray<UObject*>& NewDataInstances);

    UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
    UObject* GetDataInstance() const;
    virtual UObject* GetDataInstance_Implementation() const;

    UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
    void SetDataInstance(UObject* NewDataInstance);
    virtual void SetDataInstance_Implementation(UObject* NewDataInstance);

    UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
    UDataAsset* GetData() const;
    virtual UDataAsset* GetDataAsset_Implementation() const;

    UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
    void SetData(UDataAsset* NewData);
    virtual void SetData_Implementation(UDataAsset* NewData);
};
