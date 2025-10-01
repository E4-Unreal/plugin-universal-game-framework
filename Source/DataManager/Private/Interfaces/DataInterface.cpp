// Fill out your copyright notice in the Description page of Project Settings.


#include "Interfaces/DataInterface.h"

#include "Data/DataDefinitionBase.h"
#include "Data/DataInstanceBase.h"
#include "Interfaces/DataInstanceInterface.h"


// Add default functionality here for any IDataInterface functions that are not pure virtual.
UDataAsset* IDataInterface::GetDataByInterface_Implementation(TSubclassOf<UInterface> InterfaceClass) const
{
    auto Data = CastChecked<UDataAsset>(this);

    return InterfaceClass && Data->GetClass()->ImplementsInterface(InterfaceClass) ? const_cast<UDataAsset*>(Data) : nullptr;
}

UDataInstanceBase* IDataInterface::CreateInstanceData_Implementation() const
{
    auto Data = CastChecked<UDataDefinitionBase>(this);
    auto InstanceDataClass = IDataInterface::Execute_GetInstanceDataClass(Data);

    if (InstanceDataClass && InstanceDataClass->ImplementsInterface(UDataInstanceInterface::StaticClass()))
    {
        auto NewInstanceData = NewObject<UDataInstanceBase>(GetTransientPackage(), InstanceDataClass);
        IDataInstanceInterface::Execute_SetDefinition(NewInstanceData, const_cast<UDataDefinitionBase*>(Data));

        return NewInstanceData;
    }

    return nullptr;
}
