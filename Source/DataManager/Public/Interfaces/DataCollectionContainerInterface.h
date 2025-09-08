// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "DataCollectionContainerInterface.generated.h"

class UDataCollection;

UINTERFACE(MinimalAPI, Blueprintable, BlueprintType)
class UDataCollectionContainerInterface : public UInterface
{
    GENERATED_BODY()
};

/**
 *
 */
class DATAMANAGER_API IDataCollectionContainerInterface
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
    UDataCollection* GetDataCollection() const;

    UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
    void SetDataCollection(UDataCollection* NewDataCollection);
};
