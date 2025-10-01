// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ReplicatedObject.h"
#include "Interfaces/DataInstanceInterface.h"
#include "DataInstanceBase.generated.h"

class UDataDefinitionBase;
/**
 *
 */
UCLASS(Abstract, EditInlineNew)
class DATAMANAGER_API UDataInstanceBase : public UReplicatedObject, public IDataInstanceInterface
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config", Replicated, meta = (DisplayPriority = 0))
    TObjectPtr<UDataDefinitionBase> Definition;

public:
    /* Object */

    virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;

    /* DataObjectInterface */

    virtual UDataDefinitionBase* GetDefinition_Implementation() const override { return Definition; }
    virtual void SetDefinition_Implementation(UDataDefinitionBase* NewDefinition) override { Definition = NewDefinition; }
    virtual UObject* GetInstanceDataByInterface_Implementation(TSubclassOf<UInterface> InterfaceClass) const override;
};
