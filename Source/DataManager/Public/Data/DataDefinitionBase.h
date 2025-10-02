// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Interfaces/DataInterface.h"
#include "DataDefinitionBase.generated.h"

/**
 *
 */
UCLASS(Abstract)
class DATAMANAGER_API UDataDefinitionBase : public UPrimaryDataAsset, public IDataInterface
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config", meta = (DisplayPriority = 0))
    FName DataType;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config", meta = (DisplayPriority = 1))
    int32 ID;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config", meta = (DisplayPriority = 2))
    FText DisplayName;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config", meta = (DisplayPriority = 3))
    FText Description;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config", meta = (DisplayPriority = 4, MustImplement = "InstanceDataInterface"))
    TSubclassOf<UObject> InstanceDataClass;

public:
    UDataDefinitionBase();

    /* Object */

    virtual FPrimaryAssetId GetPrimaryAssetId() const override;

    /* DataDefinitionInterface */

    virtual TSubclassOf<UObject> GetInstanceDataClass_Implementation() const override { return InstanceDataClass; }
};
