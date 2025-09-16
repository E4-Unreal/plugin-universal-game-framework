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

protected:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
    int32 ID;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config", meta = (MustImplement = "DataInstanceInterface"))
    TSubclassOf<UObject> DataInstanceClass;

public:
    /* DataDefinitionInterface */

    virtual int32 GetID_Implementation() const override { return ID; }
    virtual void SetID_Implementation(int32 NewID) override { ID = NewID; }
    virtual UObject* CreateDataInstance_Implementation() const override;
};
