// Fill out your copyright notice in the Description page of Project Settings.


#include "Data/DataDefinitionBase.h"

#include "Interfaces/DataInstanceInterface.h"

UObject* UDataDefinitionBase::CreateInstance_Implementation() const
{
    if (InstanceClass && InstanceClass->ImplementsInterface(UDataInstanceInterface::StaticClass()))
    {
        UObject* NewInstance = NewObject<UObject>(GetTransientPackage(), InstanceClass);
        IDataInstanceInterface::Execute_SetData(NewInstance, const_cast<UDataDefinitionBase*>(this));

        return NewInstance;
    }

    return nullptr;
}

UDataAsset* UDataDefinitionBase::GetDataByInterface_Implementation(TSubclassOf<UInterface> InterfaceClass) const
{
    return InterfaceClass && GetClass()->ImplementsInterface(InterfaceClass) ? const_cast<UDataDefinitionBase*>(this) : nullptr;
}
