// Fill out your copyright notice in the Description page of Project Settings.


#include "Interfaces/DataActorInterface.h"

#include "Interfaces/DataInstanceInterface.h"
#include "Interfaces/DataInterface.h"


// Add default functionality here for any IDataActorInterface functions that are not pure virtual.
UObject* IDataActorInterface::GetDataInstance_Implementation() const
{
    TArray<UObject*> DataInstances = Execute_GetDataInstances(CastChecked<UObject>(this));

    return !DataInstances.IsEmpty() ? DataInstances[0] : nullptr;
}

void IDataActorInterface::SetDataInstance_Implementation(UObject* NewDataInstance)
{
    Execute_SetDataInstances(CastChecked<UObject>(this), { NewDataInstance });
}

UDataAsset* IDataActorInterface::GetDataAsset_Implementation() const
{
    UObject* DataInstance = Execute_GetDataInstance(CastChecked<UObject>(this));
    if (DataInstance && DataInstance->Implements<UDataInstanceInterface>())
    {
        return IDataInstanceInterface::Execute_GetData(DataInstance);
    }

    return nullptr;
}

void IDataActorInterface::SetData_Implementation(UDataAsset* NewData)
{
    if (NewData && NewData->Implements<UDataInterface>())
    {
        if (UObject* NewDataInstance = IDataInterface::Execute_CreateDataInstance(NewData))
        {
            Execute_SetDataInstance(CastChecked<UObject>(this), NewDataInstance);
        }
    }
}

