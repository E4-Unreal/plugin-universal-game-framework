// Fill out your copyright notice in the Description page of Project Settings.


#include "Data/DataDefinitionBase.h"

#include "Interfaces/InstanceDataInterface.h"

UDataAsset* UDataDefinitionBase::GetDataByInterface_Implementation(TSubclassOf<UInterface> InterfaceClass) const
{
    return InterfaceClass && GetClass()->ImplementsInterface(InterfaceClass) ? const_cast<ThisClass*>(this) : nullptr;
}

UObject* UDataDefinitionBase::CreateDataObject_Implementation() const
{
    if (DataObjectClass && DataObjectClass->ImplementsInterface(UInstanceDataInterface::StaticClass()))
    {
        auto NewInstance = NewObject<UObject>(GetTransientPackage(), DataObjectClass);
        IInstanceDataInterface::Execute_SetData(NewInstance, const_cast<ThisClass*>(this));

        return NewInstance;
    }

    return nullptr;
}
