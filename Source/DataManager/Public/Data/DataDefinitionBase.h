// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Interfaces/DataDefinitionInterface.h"
#include "DataDefinitionBase.generated.h"

/**
 *
 */
UCLASS(Abstract)
class DATAMANAGER_API UDataDefinitionBase : public UPrimaryDataAsset, public IDataDefinitionInterface
{
    GENERATED_BODY()

protected:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config", meta = (MustImplement = "DataInstanceInterface"))
    TSubclassOf<UObject> InstanceClass;

public:
    /* DataDefinitionInterface */

    virtual UObject* CreateInstance_Implementation() const override;
    virtual UDataAsset* GetDataByInterface_Implementation(TSubclassOf<UInterface> InterfaceClass) const override;
};
