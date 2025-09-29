// Fill out your copyright notice in the Description page of Project Settings.


#include "Interfaces/InstanceDataInterface.h"

#include "Interfaces/DataInterface.h"


// Add default functionality here for any IDataInstanceInterface functions that are not pure virtual.
UDataAsset* IInstanceDataInterface::GetDataByInterface_Implementation(TSubclassOf<UInterface> InterfaceClass) const
{
    auto InstanceData = Cast<UObject>(this);
    auto Data = IInstanceDataInterface::Execute_GetData(InstanceData);

    return Data && Data->Implements<UDataInterface>() ? IDataInterface::Execute_GetDataByInterface(Data, InterfaceClass) : nullptr;
}
