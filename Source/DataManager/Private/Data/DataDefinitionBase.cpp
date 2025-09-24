// Fill out your copyright notice in the Description page of Project Settings.


#include "Data/DataDefinitionBase.h"

#include "Interfaces/DataObjectInterface.h"

UObject* UDataDefinitionBase::CreateDataInstance_Implementation() const
{
    if (DataInstanceClass && DataInstanceClass->ImplementsInterface(UDataObjectInterface::StaticClass()))
    {
        auto NewInstance = NewObject<UObject>(GetTransientPackage(), DataInstanceClass);
        IDataObjectInterface::Execute_SetData(NewInstance, const_cast<ThisClass*>(this));

        return NewInstance;
    }

    return nullptr;
}
