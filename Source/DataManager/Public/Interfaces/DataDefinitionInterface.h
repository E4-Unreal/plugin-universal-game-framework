// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "DataDefinitionInterface.generated.h"

UINTERFACE(MinimalAPI, Blueprintable, BlueprintType)
class UDataDefinitionInterface : public UInterface
{
    GENERATED_BODY()
};

/**
 *
 */
class DATAMANAGER_API IDataDefinitionInterface
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
    UObject* CreateInstance() const;

    UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
    UDataAsset* GetDataByInterface(TSubclassOf<UInterface> InterfaceClass) const;
};
