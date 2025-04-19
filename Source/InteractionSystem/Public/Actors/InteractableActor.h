// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InteractableActorBase.h"
#include "Components/SphereComponent.h"
#include "InteractableActor.generated.h"

class USphereComponent;

UCLASS()
class INTERACTIONSYSTEM_API AInteractableActor : public AInteractableActorBase
{
    GENERATED_BODY()

public:
    AInteractableActor(const FObjectInitializer& ObjectInitializer);

public:
    UFUNCTION(BlueprintPure)
    FORCEINLINE UStaticMeshComponent* GetDisplayStaticMesh() const { return GetDisplayMesh<UStaticMeshComponent>(); }

    UFUNCTION(BlueprintPure)
    FORCEINLINE USphereComponent* GetOverlapSphere() const { return GetOverlapShape<USphereComponent>(); }
};
