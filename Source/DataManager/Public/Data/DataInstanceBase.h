// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DataContainerBase.h"
#include "DataInstanceBase.generated.h"

class UDataDefinitionBase;

/**
 *
 */
UCLASS(Abstract)
class DATAMANAGER_API UDataInstanceBase : public UDataContainerBase
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
    TSubclassOf<UInterface> DataInterfaceClass;

public:
    /* DataContainerBase */

    virtual void SetData_Implementation(UDataAsset* NewData) override;

    /* API */

    virtual bool CanCreateFromData(TSubclassOf<UDataAsset> DataClass);
};
