// Fill out your copyright notice in the Description page of Project Settings.


#include "Data/DataDefinitionBase.h"

#include "Interfaces/DataObjectInterface.h"

UObject* UDataDefinitionBase::CreateDataObject_Implementation() const
{
    if (DataObjectClass && DataObjectClass->ImplementsInterface(UDataObjectInterface::StaticClass()))
    {
        auto NewInstance = NewObject<UObject>(GetTransientPackage(), DataObjectClass);
        IDataObjectInterface::Execute_SetData(NewInstance, const_cast<ThisClass*>(this));

        return NewInstance;
    }

    return nullptr;
}
