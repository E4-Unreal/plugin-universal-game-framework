// Fill out your copyright notice in the Description page of Project Settings.


#include "Data/DataCollection.h"

#include "Data/DataDefinitionBase.h"
#include "Data/DataInstanceBase.h"
#include "Interfaces/DataInstanceInterface.h"
#include "Net/UnrealNetwork.h"

void UDataCollection::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);

    DOREPLIFETIME(ThisClass, Instances);
}

bool UDataCollection::IsValid_Implementation() const
{
    return Super::IsValid_Implementation() && !Instances.IsEmpty();
}

void UDataCollection::SetData_Implementation(UDataAsset* NewData)
{
    if (NewData && NewData->Implements<UDataDefinitionInterface>())
    {
        TArray<UObject*> NewInstances;
        const auto& InstanceClasses = IDataDefinitionInterface::Execute_GetInstanceClasses(NewData);
        for (const auto& InstanceClass : InstanceClasses)
        {
            if (InstanceClass && InstanceClass->ImplementsInterface(UDataInstanceInterface::StaticClass()))
            {
                auto NewInstance = NewObject<UObject>(GetTransientPackage(), InstanceClass);
                IDataInstanceInterface::Execute_SetData(NewInstance, NewData);
                if (IDataInstanceInterface::Execute_IsValid(NewInstance)) NewInstances.Emplace(NewInstance);
            }
        }

        Instances = NewInstances;
    }
}

UDataAsset* UDataCollection::GetDataByInterface_Implementation(TSubclassOf<UInterface> InterfaceClass) const
{
    if (InterfaceClass == nullptr) return nullptr;

    if (Data && Data->GetClass()->ImplementsInterface(InterfaceClass))
    {
        return Data;
    }
    else
    {
        for (auto Instance : Instances)
        {
            if (Instance && Instance->Implements<UDataContainerInterface>())
            {
                UDataAsset* InstanceData = IDataContainerInterface::Execute_GetData(Instance);
                if (InstanceData && InstanceData->GetClass()->ImplementsInterface(InterfaceClass))
                {
                    return InstanceData;
                }
            }
        }
    }

    return nullptr;
}

UObject* UDataCollection::GetInstanceByInterface_Implementation(TSubclassOf<UInterface> InterfaceClass) const
{
    for (auto Instance : Instances)
    {
        if (Instance && Instance->GetClass()->ImplementsInterface(InterfaceClass))
        {
            return Instance;
        }
    }

    return nullptr;
}

UDataCollection* UDataCollection::CreateDataCollectionFromData(UDataAsset* InData)
{
    if (InData)
    {
        auto NewCollection = NewObject<UDataCollection>();
        if (NewCollection && NewCollection->Implements<UDataInstanceInterface>())
        {
            IDataInstanceInterface::Execute_SetData(NewCollection, InData);

            return IDataInstanceInterface::Execute_IsValid(NewCollection) ? NewCollection : nullptr;
        }
    }

    return nullptr;
}
