// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Data/ReplicatedObject.h"
#include "FlexibleDataInstanceBase.generated.h"

class UDataInstanceFragment;

/**
 *
 */
UCLASS(Abstract)
class DATAMANAGER_API UFlexibleDataInstanceBase : public UReplicatedObject
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config", meta = (DisplayPriority = 0))
    TObjectPtr<UDataAsset> Data;

public:
    /* API */

    UFUNCTION(BlueprintPure)
    virtual UDataInstanceFragment* GetFragmentByInterface(const TSubclassOf<UInterface> InterfaceClass) const { return nullptr; }
};
