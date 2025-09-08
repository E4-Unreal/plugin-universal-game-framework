// Fill out your copyright notice in the Description page of Project Settings.


#include "Data/DataCollection.h"

#include "Data/DataDefinitionBase.h"
#include "Data/DataInstanceBase.h"
#include "Net/UnrealNetwork.h"

void UDataCollection::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);

    DOREPLIFETIME(ThisClass, Instances);
}

void UDataCollection::SetData_Implementation(UDataAsset* NewData)
{
    Super::SetData_Implementation(NewData);

    if (UDataDefinitionBase* Definition = Cast<UDataDefinitionBase>(Data))
    {
        SetInstances(Definition->CreateInstances());
    }
}

bool UDataCollection::HasDataByInterface(TSubclassOf<UInterface> InterfaceClass) const
{
    return GetDataByInterface(InterfaceClass) != nullptr;
}

UDataAsset* UDataCollection::GetDataByInterface(TSubclassOf<UInterface> InterfaceClass) const
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

bool UDataCollection::HasInstanceByInterface(TSubclassOf<UInterface> InterfaceClass) const
{
    return GetInstanceByInterface(InterfaceClass) != nullptr;
}

UObject* UDataCollection::GetInstanceByInterface(TSubclassOf<UInterface> InterfaceClass) const
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
