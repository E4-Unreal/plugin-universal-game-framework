// Fill out your copyright notice in the Description page of Project Settings.


#include "FunctionLibraries/DataManagerFunctionLibrary.h"

#include "Interfaces/DataInterface.h"
#include "Interfaces/InstanceDataInterface.h"

UDataAsset* UDataManagerFunctionLibrary::GetDataByInterface(UObject* DataObject, TSubclassOf<UInterface> InterfaceClass)
{
    if (DataObject && InterfaceClass)
    {
        if (DataObject->Implements<UDataInterface>())
        {
            return IDataInterface::Execute_GetDataByInterface(DataObject, InterfaceClass);
        }
        else if (DataObject->Implements<UInstanceDataInterface>())
        {
            return IInstanceDataInterface::Execute_GetDataByInterface(DataObject, InterfaceClass);
        }
    }

    return nullptr;
}

UObject* UDataManagerFunctionLibrary::GetInstanceDataByInterface(UObject* InstanceData,
    TSubclassOf<UInterface> InterfaceClass)
{
    if (InstanceData && InterfaceClass && InstanceData->Implements<UInstanceDataInterface>())
    {
        return IInstanceDataInterface::Execute_GetInstanceDataByInterface(InstanceData, InterfaceClass);
    }

    return nullptr;
}

bool UDataManagerFunctionLibrary::SupportsDataInterfaces(UDataAsset* Data,
                                                         const TArray<TSubclassOf<UInterface>>& InterfaceClasses)
{
    if (Data && Data->Implements<UDataInterface>())
    {
        for (auto InterfaceClass : InterfaceClasses)
        {
            if (InterfaceClass == nullptr) continue;

            if (GetDataByInterface(Data, InterfaceClass) == nullptr) return false;
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

            if (GetInstanceDataByInterface(InstanceData, InterfaceClass) == nullptr && GetDataByInterface(InstanceData, InterfaceClass) == nullptr) return false;
        }

        return true;
    }

    return false;
}
