// Fill out your copyright notice in the Description page of Project Settings.


#include "Data/DataDefinitionBase.h"

#include "Data/DataCollection.h"
#include "Data/DataInstanceBase.h"

UDataCollection* UDataDefinitionBase::CreateCollection() const
{
    UDataCollection* NewCollection = NewObject<UDataCollection>();
    NewCollection->SetDefinition(const_cast<UDataDefinitionBase*>(this));

    return NewCollection;
}

TArray<UDataInstanceBase*> UDataDefinitionBase::CreateInstances() const
{
    TArray<UDataInstanceBase*> NewInstances;
    NewInstances.Reserve(InstanceClasses.Num());

    for (TSubclassOf<UDataInstanceBase> InstanceClass : InstanceClasses)
    {
        if (UDataInstanceBase* NewInstance = CreateInstance(InstanceClass))
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
        if (UDataInstanceBase* DefaultInstance = InstanceClass->GetDefaultObject<UDataInstanceBase>())
        {
            return DefaultInstance->CanCreateFromData(GetClass());
        }
    }

    return false;
}

UDataInstanceBase* UDataDefinitionBase::CreateInstance(TSubclassOf<UDataInstanceBase> InstanceClass) const
{
    if (InstanceClass)
    {
        UDataInstanceBase* NewInstance = NewObject<UDataInstanceBase>(GetTransientPackage(), InstanceClass);
        NewInstance->SetDefinition(const_cast<UDataDefinitionBase*>(this));

        return NewInstance->IsValid() ? NewInstance : nullptr;
    }

    return nullptr;
}
