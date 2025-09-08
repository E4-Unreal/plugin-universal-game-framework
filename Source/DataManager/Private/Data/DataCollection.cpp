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

void UDataCollection::SetDefinition_Implementation(UDataDefinitionBase* NewDefinition)
{
    Super::SetDefinition_Implementation(NewDefinition);

    if (Definition) SetInstances(Definition->CreateInstances());
}

UDataInstanceBase* UDataCollection::GetInstanceByInterface_Implementation(TSubclassOf<UInterface> Interface) const
{
    for (UDataInstanceBase* Instance : Instances)
    {
        if (Instance && Instance->GetClass()->ImplementsInterface(Interface))
        {
            return Instance;
        }
    }

    return nullptr;
}
