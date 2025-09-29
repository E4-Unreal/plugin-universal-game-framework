// Fill out your copyright notice in the Description page of Project Settings.


#include "Interfaces/DataInterface.h"

#include "Interfaces/DataInstanceInterface.h"


// Add default functionality here for any IDataInterface functions that are not pure virtual.
UDataAsset* IDataInterface::GetDataByInterface_Implementation(TSubclassOf<UInterface> InterfaceClass) const
{
    auto Data = CastChecked<UDataAsset>(this);

    return InterfaceClass && Data->GetClass()->ImplementsInterface(InterfaceClass) ? const_cast<UDataAsset*>(Data) : nullptr;
}

UObject* IDataInterface::CreateInstanceData_Implementation() const
{
    auto Data = CastChecked<UDataAsset>(this);
    auto InstanceDataClass = IDataInterface::Execute_GetInstanceDataClass(Data);

    if (InstanceDataClass && InstanceDataClass->ImplementsInterface(UDataInstanceInterface::StaticClass()))
    {
        auto NewInstanceData = NewObject<UObject>(GetTransientPackage(), InstanceDataClass);
        IDataInstanceInterface::Execute_SetData(NewInstanceData, const_cast<UDataAsset*>(Data));

        return NewInstanceData;
    }

    return nullptr;
}
