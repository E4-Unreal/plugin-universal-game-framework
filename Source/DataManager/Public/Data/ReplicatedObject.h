// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "ReplicatedObject.generated.h"

/**
 *
 */
UCLASS(Blueprintable)
class DATAMANAGER_API UReplicatedObject : public UObject
{
    GENERATED_BODY()

public:
    virtual bool IsSupportedForNetworking() const override { return true; }
};
