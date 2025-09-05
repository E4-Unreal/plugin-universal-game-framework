// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/ReplicatedComponent.h"

#include "Net/UnrealNetwork.h"

UReplicatedComponent::UReplicatedComponent()
{
    SetIsReplicatedByDefault(true);
    bReplicateUsingRegisteredSubObjectList = true;
}

void UReplicatedComponent::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);

    DOREPLIFETIME(ThisClass, ReplicatedObjects);
}

UReplicatedObject* UReplicatedComponent::CreateReplicatedObject(TSubclassOf<UReplicatedObject> ReplicatedObjectClass)
{
    UReplicatedObject* ReplicatedObject = nullptr;

    if (GetOwner()->HasAuthority() && ReplicatedObjectClass)
    {
        ReplicatedObject = NewObject<UReplicatedObject>(this, ReplicatedObjectClass);
        AddReplicatedObject(ReplicatedObject);
    }

    return ReplicatedObject;
}

void UReplicatedComponent::AddReplicatedObject(UReplicatedObject* ReplicatedObject)
{
    if (GetOwner()->HasAuthority() && ReplicatedObject)
    {
        ReplicatedObjects.Emplace(ReplicatedObject);

        AddReplicatedSubObject(ReplicatedObject);
    }
}

void UReplicatedComponent::RemoveReplicatedObject(UReplicatedObject* ReplicatedObject)
{
    if (GetOwner()->HasAuthority() && ReplicatedObject)
    {
        RemoveReplicatedSubObject(ReplicatedObject);

        ReplicatedObjects.RemoveSingleSwap(ReplicatedObject);
    }
}
