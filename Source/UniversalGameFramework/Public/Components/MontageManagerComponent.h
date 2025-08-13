// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "MontageManagerComponent.generated.h"


UCLASS(meta = (BlueprintSpawnableComponent))
class UNIVERSALGAMEFRAMEWORK_API UMontageManagerComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    UMontageManagerComponent(const FObjectInitializer& ObjectInitializer);
};
