// Fill out your copyright notice in the Description page of Project Settings.


#include "FunctionLibraries/DataManagerFunctionLibrary.h"

#include "Interfaces/DataInterface.h"
#include "Interfaces/DataInstanceInterface.h"

UDataAsset* UDataManagerFunctionLibrary::GetData(UObject* DataObject)
{
    return GetDataByInterface<UDataInterface>(DataObject);
}

int32 UDataManagerFunctionLibrary::GetID(UObject* DataObject)
{
    auto Data = GetData(DataObject);

    return Data ? IDataInterface::Execute_GetID(Data) : -1;
}

FText UDataManagerFunctionLibrary::GetDisplayName(UObject* DataObject)
{
    auto Data = GetData(DataObject);

    return Data ? IDataInterface::Execute_GetDisplayName(Data) : FText::GetEmpty();
}

FText UDataManagerFunctionLibrary::GetDescription(UObject* DataObject)
{
    auto Data = GetData(DataObject);

    return Data ? IDataInterface::Execute_GetDescription(Data) : FText::GetEmpty();
}

UDataAsset* UDataManagerFunctionLibrary::GetDataByInterface(UObject* DataObject, TSubclassOf<UInterface> InterfaceClass)
{
    if (DataObject && InterfaceClass)
    {
        if (DataObject->Implements<UDataInterface>())
        {
            return IDataInterface::Execute_GetDataByInterface(DataObject, InterfaceClass);
        }
        else if (DataObject->Implements<UDataInstanceInterface>())
        {
            return IDataInstanceInterface::Execute_GetDataByInterface(DataObject, InterfaceClass);
        }
    }

    return nullptr;
}

UObject* UDataManagerFunctionLibrary::GetInstanceDataByInterface(UObject* InstanceData,
    TSubclassOf<UInterface> InterfaceClass)
{
    if (InstanceData && InterfaceClass && InstanceData->Implements<UDataInstanceInterface>())
    {
        return IDataInstanceInterface::Execute_GetInstanceDataByInterface(InstanceData, InterfaceClass);
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
    if (InstanceData && InstanceData->Implements<UDataInstanceInterface>())
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

UObject* UDataManagerFunctionLibrary::CreateInstanceData(UDataAsset* Data)
{
    return Data && Data->Implements<UDataInterface>() ? IDataInterface::Execute_CreateInstanceData(Data) : nullptr;
}
