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
    /**
     *
     * @param DataObject Data or InstanceData
     * @param InterfaceClass DataInterface
     * @return Data
     */
    UFUNCTION(BLueprintCallable)
    static UDataAsset* GetDataByInterface(UObject* DataObject, TSubclassOf<UInterface> InterfaceClass);

    template <typename TInterface = UInterface>
    static UDataAsset* GetDataByInterface(UObject* DataObject)
    {
        return GetDataByInterface(DataObject, TInterface::StaticClass());
    }

    UFUNCTION(BlueprintCallable)
    static UObject* GetInstanceDataByInterface(UObject* InstanceData, TSubclassOf<UInterface> InterfaceClass);

    template <typename TInterface = UInterface>
    static UObject* GetInstanceDataByInterface(UObject* InstanceData)
    {
        return GetInstanceDataByInterface(InstanceData, TInterface::StaticClass());
    }

    UFUNCTION(BlueprintCallable)
    static bool SupportsDataInterfaces(UDataAsset* Data, const TArray<TSubclassOf<UInterface>>& InterfaceClasses);

    UFUNCTION(BlueprintCallable)
    static bool SupportsInstanceDataInterfaces(UObject* InstanceData, const TArray<TSubclassOf<UInterface>>& InterfaceClasses);

    UFUNCTION(BlueprintCallable)
    static UObject* CreateInstanceData(UDataAsset* Data);
};
