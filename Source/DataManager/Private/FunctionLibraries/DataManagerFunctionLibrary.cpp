// Fill out your copyright notice in the Description page of Project Settings.


#include "FunctionLibraries/DataManagerFunctionLibrary.h"

#include "Interfaces/DataInterface.h"
#include "Interfaces/DataObjectInterface.h"

bool UDataManagerFunctionLibrary::SupportsInterfaces(UObject* DataObject, const TArray<TSubclassOf<UInterface>>& InterfaceClasses)
{
    bool bResult = false;

    if (DataObject)
    {
        if (DataObject->Implements<UDataInterface>())
        {
            bResult = true;

            for (auto InterfaceClass : InterfaceClasses)
            {
                if (InterfaceClass == nullptr) continue;

                if (IDataInterface::Execute_GetDataByInterface(DataObject, InterfaceClass) == nullptr) bResult = false;
            }
        }
        else if (DataObject->Implements<UDataObjectInterface>())
        {
            bResult = true;

            for (auto InterfaceClass : InterfaceClasses)
            {
                if (InterfaceClass == nullptr) continue;

                if (IDataObjectInterface::Execute_GetDataObjectByInterface(DataObject, InterfaceClass) == nullptr) bResult = false;
            }
        }
    }

    return bResult;
}
