// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InteractableActorBase.h"
#include "InteractableActor.generated.h"

UCLASS()
class INTERACTIONSYSTEM_API AInteractableActor : public AInteractableActorBase
{
    GENERATED_BODY()

public:
    AInteractableActor(const FObjectInitializer& ObjectInitializer);
};
