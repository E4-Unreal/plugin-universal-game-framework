// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "DataObjectInterface.generated.h"

UINTERFACE(MinimalAPI, Blueprintable, BlueprintType)
class UDataObjectInterface : public UInterface
{
    GENERATED_BODY()
};

/**
 *
 */
class DATAMANAGER_API IDataObjectInterface
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
    UDataAsset* GetData() const;

    UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
    void SetData(UDataAsset* NewData);
};
