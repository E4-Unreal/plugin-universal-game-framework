// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ReplicatedObject.h"
#include "Interfaces/DataInstanceInterface.h"
#include "DataInstanceBase.generated.h"

/**
 *
 */
UCLASS(Abstract, EditInlineNew)
class DATAMANAGER_API UDataInstanceBase : public UReplicatedObject, public IDataInstanceInterface
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config", Replicated, meta = (DisplayPriority = 0))
    TObjectPtr<UDataAsset> Data;

public:
    /* Object */

    virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;

    /* DataObjectInterface */

    virtual UDataAsset* GetData_Implementation() const override { return Data; }
    virtual void SetData_Implementation(UDataAsset* NewData) override { Data = NewData; }
    virtual UObject* GetInstanceDataByInterface_Implementation(TSubclassOf<UInterface> InterfaceClass) const override;
};
