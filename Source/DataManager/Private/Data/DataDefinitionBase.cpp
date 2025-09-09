// Fill out your copyright notice in the Description page of Project Settings.


#include "Data/DataDefinitionBase.h"

#include "Data/DataInstanceBase.h"

UDataInstanceBase* UDataDefinitionBase::CreateInstance_Implementation() const
{
    if (InstanceClass)
    {
        auto NewInstance = NewObject<UDataInstanceBase>(GetTransientPackage(), InstanceClass);
        NewInstance->SetData(const_cast<ThisClass*>(this));

        return NewInstance;
    }

    return nullptr;
}

UDataAsset* UDataDefinitionBase::GetDataByInterface_Implementation(TSubclassOf<UInterface> InterfaceClass) const
{
    return InterfaceClass && GetClass()->ImplementsInterface(InterfaceClass) ? const_cast<UDataDefinitionBase*>(this) : nullptr;
}
