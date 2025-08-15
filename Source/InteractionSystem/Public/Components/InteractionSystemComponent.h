// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InteractionSystemComponent.generated.h"

class IInteractableInterface;

UCLASS(meta = (BlueprintSpawnableComponent))
class INTERACTIONSYSTEM_API UInteractionSystemComponent : public UActorComponent
{
    GENERATED_BODY()

protected:
    UPROPERTY(VisibleAnywhere, Transient, Category = "State")
    TArray<TScriptInterface<IInteractableInterface>> AvailableTargets;

    UPROPERTY(VisibleAnywhere, Transient, Category = "State")
    TScriptInterface<IInteractableInterface> CurrentTarget;

public:
    UFUNCTION(BlueprintCallable)
    virtual void AddTarget(const TScriptInterface<IInteractableInterface>& NewTarget);

    UFUNCTION(BlueprintCallable)
    virtual void RemoveTarget(const TScriptInterface<IInteractableInterface>& OldTarget);

    UFUNCTION(BlueprintCallable)
    virtual void TryInteract();

    UFUNCTION(BlueprintCallable)
    virtual void CancelInteract();

protected:
    virtual void RefreshTarget();

    float CalculateTargetDistance(const TScriptInterface<IInteractableInterface>& Target) const;
};
