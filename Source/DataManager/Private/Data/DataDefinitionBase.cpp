// Fill out your copyright notice in the Description page of Project Settings.


#include "Data/DataDefinitionBase.h"

#include "Data/DataInstanceContainer.h"
#include "Data/DataInstanceBase.h"

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

    for (TSubclassOf<UObject> InstanceClass : InstanceClasses)
    {
        if (UObject* NewInstance = CreateInstance(InstanceClass))
        {
            NewInstances.Emplace(NewInstance);
        }
    }

    return NewInstances;
}

bool UDataDefinitionBase::CanCreateInstance(TSubclassOf<UObject> InstanceClass) const
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

UObject* UDataDefinitionBase::CreateInstance(TSubclassOf<UObject> InstanceClass) const
{
    if (InstanceClass)
    {
        UDataInstanceBase* NewInstance = NewObject<UDataInstanceBase>(GetTransientPackage(), InstanceClass);
        NewInstance->SetData(const_cast<UDataDefinitionBase*>(this));

        return NewInstance->IsValid() ? NewInstance : nullptr;
    }

    return nullptr;
}
