// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "ModelInjectableInterface.generated.h"

UINTERFACE(MinimalAPI, BlueprintType, Blueprintable)
class UModelInjectableInterface : public UInterface
{
    GENERATED_BODY()
};

/**
 *
 */
class MVVMEXTENSIONS_API IModelInjectableInterface
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
    void SetModel(UObject* NewModel);
};
