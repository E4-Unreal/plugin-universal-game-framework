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
    int32 GetID() const;

    UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
    void SetID(int32 NewID);

    UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
    FText GetDisplayName() const;

    UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
    void SetDisplayName(const FText& NewDisplayName);

    UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
    FText GetDescription() const;

    UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
    void SetDescription(const FText& NewDescription);

    UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
    UDataAsset* GetDataByInterface(TSubclassOf<UInterface> InterfaceClass) const;
    virtual UDataAsset* GetDataByInterface_Implementation(TSubclassOf<UInterface> InterfaceClass) const;

    UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
    TSubclassOf<UObject> GetInstanceDataClass() const;

    UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
    UObject* CreateInstanceData() const;
    virtual UObject* CreateInstanceData_Implementation() const;
};
