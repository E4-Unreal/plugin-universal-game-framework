// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "DataInstanceInterface.generated.h"

class UDataDefinitionBase;

UINTERFACE(MinimalAPI, Blueprintable, BlueprintType)
class UDataInstanceInterface : public UInterface
{
    GENERATED_BODY()
};

/**
 *
 */
class DATAMANAGER_API IDataInstanceInterface
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
    UDataDefinitionBase* GetDefinition() const;

    UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
    void SetDefinition(UDataDefinitionBase* NewDefinition);

    UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
    UObject* GetInstanceDataByInterface(TSubclassOf<UInterface> InterfaceClass) const;
    virtual UObject* GetInstanceDataByInterface_Implementation(TSubclassOf<UInterface> InterfaceClass) const;

    UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
    UDataAsset* GetDataByInterface(TSubclassOf<UInterface> InterfaceClass) const;
    virtual UDataAsset* GetDataByInterface_Implementation(TSubclassOf<UInterface> InterfaceClass) const;
};
