// Fill out your copyright notice in the Description page of Project Settings.


#include "FunctionLibraries/DataManagerFunctionLibrary.h"

#include "Interfaces/DataInterface.h"
#include "Interfaces/InstanceDataInterface.h"

bool UDataManagerFunctionLibrary::SupportsDataInterfaces(UDataAsset* Data,
    const TArray<TSubclassOf<UInterface>>& InterfaceClasses)
{
    if (Data && Data->Implements<UDataInterface>())
    {
        for (auto InterfaceClass : InterfaceClasses)
        {
            if (InterfaceClass == nullptr) continue;

            if (IDataInterface::Execute_GetDataByInterface(Data, InterfaceClass) == nullptr) return false;
        }

        return true;
    }

    return false;
}

bool UDataManagerFunctionLibrary::SupportsInstanceDataInterfaces(UObject* InstanceData,
    const TArray<TSubclassOf<UInterface>>& InterfaceClasses)
{
    if (InstanceData && InstanceData->Implements<UInstanceDataInterface>())
    {
        for (auto InterfaceClass : InterfaceClasses)
        {
            if (InterfaceClass == nullptr) continue;

            if (IInstanceDataInterface::Execute_GetInstanceDataByInterface(InstanceData, InterfaceClass) == nullptr && IInstanceDataInterface::Execute_GetDataByInterface(InstanceData, InterfaceClass) == nullptr) return false;
        }

        return true;
    }

    return false;
}
