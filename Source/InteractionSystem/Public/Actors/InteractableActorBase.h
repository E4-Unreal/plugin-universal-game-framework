// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interfaces/InteractableInterface.h"
#include "InteractableActorBase.generated.h"

class UInteractableComponent;

UCLASS(Abstract)
class INTERACTIONSYSTEM_API AInteractableActorBase : public AActor, public IInteractableInterface
{
    GENERATED_BODY()

protected:
    static FName InteractableComponentName;

private:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component", meta = (AllowPrivateAccess = "true"))
    TObjectPtr<UInteractableComponent> InteractableComponent;

public:
    AInteractableActorBase(const FObjectInitializer& ObjectInitializer);

public:
    FORCEINLINE UInteractableComponent* GetInteractableComponent() const { return InteractableComponent; }
};
