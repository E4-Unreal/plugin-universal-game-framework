// Fill out your copyright notice in the Description page of Project Settings.


#include "Interfaces/DataInstanceInterface.h"

#include "Data/DataDefinitionBase.h"
#include "Data/DataInstanceBase.h"
#include "Interfaces/DataInterface.h"


// Add default functionality here for any IDataInstanceInterface functions that are not pure virtual.
UObject* IDataInstanceInterface::GetInstanceDataByInterface_Implementation(TSubclassOf<UInterface> InterfaceClass) const
{
    auto InstanceData = CastChecked<UObject>(this);

    return InterfaceClass && InstanceData->GetClass()->ImplementsInterface(InterfaceClass) ? const_cast<UObject*>(InstanceData) : nullptr;
}

UDataAsset* IDataInstanceInterface::GetDataByInterface_Implementation(TSubclassOf<UInterface> InterfaceClass) const
{
    auto DataInstance = CastChecked<UDataInstanceBase>(this);
    auto Data = DataInstance->Definition;

    return Data && Data->Implements<UDataInterface>() ? IDataInterface::Execute_GetDataByInterface(Data, InterfaceClass) : nullptr;
}
