// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DefinitionContainerBase.h"
#include "DataInstanceBase.generated.h"

class UDataDefinitionBase;

/**
 *
 */
UCLASS(Abstract)
class DATAMANAGER_API UDataInstanceBase : public UDefinitionContainerBase
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
    TSubclassOf<UInterface> DefinitionInterfaceClass;

public:
    /* DefinitionContainerBase */

    virtual void SetDefinition_Implementation(UDataDefinitionBase* NewDefinition) override;
};
