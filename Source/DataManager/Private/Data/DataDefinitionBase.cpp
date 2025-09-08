// Fill out your copyright notice in the Description page of Project Settings.


#include "Data/DataDefinitionBase.h"

#include "Data/DataInstanceBase.h"
#include "Data/DataInstanceContainer.h"

UDataInstanceContainer* UDataDefinitionBase::CreateCollection() const
{
    UDataInstanceContainer* NewCollection = NewObject<UDataInstanceContainer>();
    NewCollection->SetData(const_cast<UDataDefinitionBase*>(this));

    return NewCollection;
}

TArray<UObject*> UDataDefinitionBase::CreateInstances() const
{
    TArray<UObject*> NewInstances;
    NewInstances.Reserve(InstanceClasses.Num());

    for (auto InstanceClass : InstanceClasses)
    {
        if (auto NewInstance = CreateInstance(InstanceClass))
        {
            NewInstances.Emplace(NewInstance);
        }
    }

    return NewInstances;
}

bool UDataDefinitionBase::CanCreateInstance(TSubclassOf<UDataInstanceBase> InstanceClass) const
{
    if (InstanceClass)
    {
        if (auto DefaultInstance = InstanceClass->GetDefaultObject<UDataInstanceBase>())
        {
            return DefaultInstance->CanBeCreatedFromData(const_cast<UDataDefinitionBase*>(this));
        }
    }

    return false;
}

UObject* UDataDefinitionBase::CreateInstance(TSubclassOf<UDataInstanceBase> InstanceClass) const
{
    if (InstanceClass)
    {
        UDataInstanceBase* NewInstance = NewObject<UDataInstanceBase>(GetTransientPackage(), InstanceClass);
        NewInstance->SetData(const_cast<UDataDefinitionBase*>(this));

        return NewInstance->IsValid() ? NewInstance : nullptr;
    }

    return nullptr;
}
