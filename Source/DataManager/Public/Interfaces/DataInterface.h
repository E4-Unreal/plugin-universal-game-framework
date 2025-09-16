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
    UObject* CreateDataInstance() const;
};
