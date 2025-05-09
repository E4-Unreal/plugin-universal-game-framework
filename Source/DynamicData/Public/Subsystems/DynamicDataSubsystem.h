// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/EngineSubsystem.h"
#include "DynamicDataSubsystem.generated.h"

class UDefinitionBase;

/**
 *
 */
UCLASS()
class DYNAMICDATA_API UDynamicDataSubsystem : public UEngineSubsystem
{
    GENERATED_BODY()

public:
    /* Subsystem */

    virtual bool ShouldCreateSubsystem(UObject* Outer) const override;

    UFUNCTION(BlueprintCallable)
    virtual UDefinitionBase* GetDefinition(TSubclassOf<UDefinitionBase> DefinitionClass, int32 ID);

    template <typename T = UDefinitionBase>
    T* GetDefinition(int32 ID)
    {
        return Cast<T>(GetDefinition(T::StaticClass(), ID));
    }
};
