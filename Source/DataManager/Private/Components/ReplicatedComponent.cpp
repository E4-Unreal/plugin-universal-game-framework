// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/ReplicatedComponent.h"

UReplicatedComponent::UReplicatedComponent()
{
    SetIsReplicatedByDefault(true);
    bReplicateUsingRegisteredSubObjectList = true;
}

UReplicatedObject* UReplicatedComponent::CreateReplicatedObject(TSubclassOf<UReplicatedObject> ReplicatedObjectClass)
{
    UReplicatedObject* NewReplicatedObject = nullptr;

    if (GetOwner()->HasAuthority() && ReplicatedObjectClass)
    {
        NewReplicatedObject = NewObject<UReplicatedObject>(this, ReplicatedObjectClass);
        ReplicatedObjects.Emplace(NewReplicatedObject);

        AddReplicatedSubObject(NewReplicatedObject);
    }

    return NewReplicatedObject;
}

void UReplicatedComponent::DestroyReplicatedObject(UReplicatedObject* ReplicatedObject)
{
    if (GetOwner()->HasAuthority() && ReplicatedObject)
    {
        RemoveReplicatedSubObject(ReplicatedObject);

        ReplicatedObjects.RemoveSingleSwap(ReplicatedObject);
    }
}
