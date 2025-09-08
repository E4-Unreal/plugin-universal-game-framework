// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "DataInstanceContainerInterface.generated.h"

UINTERFACE(MinimalAPI, Blueprintable, BlueprintType)
class UDataInstanceContainerInterface : public UInterface
{
    GENERATED_BODY()
};

/**
 *
 */
class DATAMANAGER_API IDataInstanceContainerInterface
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
    UObject* GetInstance() const;

    UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
    void SetInstance(UObject* NewInstance);
};
