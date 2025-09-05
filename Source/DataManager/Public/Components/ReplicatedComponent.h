// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Data/ReplicatedObject.h"
#include "ReplicatedComponent.generated.h"


class UReplicatedObject;

UCLASS(meta=(BlueprintSpawnableComponent))
class DATAMANAGER_API UReplicatedComponent : public UActorComponent
{
    GENERATED_BODY()

protected:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State", Transient, Replicated)
    TArray<TObjectPtr<UReplicatedObject>> ReplicatedObjects;

public:
    UReplicatedComponent();

    /* Object */

    virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;

protected:
    virtual UReplicatedObject* CreateReplicatedObject(TSubclassOf<UReplicatedObject> ReplicatedObjectClass);
    virtual void DestroyReplicatedObject(UReplicatedObject* ReplicatedObject);

    template <typename TReplicatedObject = UReplicatedObject>
    TReplicatedObject* CreateReplicatedObject(TSubclassOf<UReplicatedObject> ReplicatedObjectClass = TReplicatedObject::StaticClass())
    {
        if (ReplicatedObjectClass && ReplicatedObjectClass->IsChildOf<TReplicatedObject>())
        {
            return Cast<TReplicatedObject>(CreateReplicatedObject(ReplicatedObjectClass));
        }

        return nullptr;
    }
};
