// Fill out your copyright notice in the Description page of Project Settings.


#include "Data/DataInstanceContainer.h"

#include "Data/DataDefinitionBase.h"
#include "Data/DataInstanceBase.h"
#include "Net/UnrealNetwork.h"

void UDataInstanceContainer::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);

    DOREPLIFETIME(ThisClass, Instances);
}

void UDataInstanceContainer::SetData_Implementation(UDataAsset* NewData)
{
    Super::SetData_Implementation(NewData);

    if (UDataDefinitionBase* Definition = Cast<UDataDefinitionBase>(Data))
    {
        SetInstances(Definition->CreateInstances());
    }
}

bool UDataInstanceContainer::HasInstanceByInterface(TSubclassOf<UInterface> InterfaceClass) const
{
    for (auto Instance : Instances)
    {
        if (Instance && Instance->GetClass()->ImplementsInterface(InterfaceClass))
        {
            return true;
        }
    }

    return false;
}

UObject* UDataInstanceContainer::GetInstanceByInterface(TSubclassOf<UInterface> InterfaceClass) const
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
