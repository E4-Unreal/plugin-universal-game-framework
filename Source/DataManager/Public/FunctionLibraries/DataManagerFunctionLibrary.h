// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "DataManagerFunctionLibrary.generated.h"

/**
 *
 */
UCLASS()
class DATAMANAGER_API UDataManagerFunctionLibrary : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable)
    static bool SupportsDataInterfaces(UDataAsset* Data, const TArray<TSubclassOf<UInterface>>& InterfaceClasses);

    UFUNCTION(BlueprintCallable)
    static bool SupportsInstanceDataInterfaces(UObject* InstanceData, const TArray<TSubclassOf<UInterface>>& InterfaceClasses);
};
