// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "DataInterface.generated.h"

class UDataInstanceBase;

UINTERFACE(MinimalAPI, Blueprintable, BlueprintType)
class UDataInterface : public UInterface
{
    GENERATED_BODY()
};

/**
 *
 */
class DATAMANAGER_API IDataInterface
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
    UDataAsset* GetDataByInterface(TSubclassOf<UInterface> InterfaceClass) const;
    virtual UDataAsset* GetDataByInterface_Implementation(TSubclassOf<UInterface> InterfaceClass) const;

    UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
    TSubclassOf<UObject> GetInstanceDataClass() const;

    UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
    UDataInstanceBase* CreateInstanceData() const;
    virtual UDataInstanceBase* CreateInstanceData_Implementation() const;
};
