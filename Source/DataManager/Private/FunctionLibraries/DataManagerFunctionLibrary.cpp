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
        if (DataObject->GetClass()->ImplementsInterface(InterfaceClass))
        {
            return Cast<UDataAsset>(DataObject);
        }
        else if (DataObject->Implements<UDataInterface>())
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
    if (InstanceData && InterfaceClass)
    {
        if (InstanceData->GetClass()->ImplementsInterface(InterfaceClass))
        {
            return InstanceData;
        }
        else if (InstanceData->Implements<UDataInstanceInterface>())
        {
            return IDataInstanceInterface::Execute_GetInstanceDataByInterface(InstanceData, InterfaceClass);
        }
    }

    return nullptr;
}

UDataInstanceBase* UDataManagerFunctionLibrary::CreateDataInstance(UDataAsset* Data)
{
    return Data && Data->Implements<UDataInterface>() ? IDataInterface::Execute_CreateInstanceData(Data) : nullptr;
}
