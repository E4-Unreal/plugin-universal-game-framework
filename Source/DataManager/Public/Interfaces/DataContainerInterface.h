// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "DataContainerInterface.generated.h"

UINTERFACE(MinimalAPI, Blueprintable, BlueprintType)
class UDataContainerInterface : public UInterface
{
    GENERATED_BODY()
};

/**
 *
 */
class DATAMANAGER_API IDataContainerInterface
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
    UDataAsset* GetData() const;

    UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
    void SetData(UDataAsset* NewData);
};
