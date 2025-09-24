// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ReplicatedObject.h"
#include "Interfaces/DataObjectInterface.h"
#include "DataObjectBase.generated.h"

/**
 *
 */
UCLASS(Abstract, EditInlineNew)
class DATAMANAGER_API UDataObjectBase : public UReplicatedObject, public IDataObjectInterface
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config", Replicated, meta = (DisplayPriority = 0))
    TObjectPtr<UDataAsset> Data;

public:
    /* Object */

    virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;

    /* DataInstanceInterface */

    virtual UDataAsset* GetData_Implementation() const override { return Data; }
    virtual void SetData_Implementation(UDataAsset* NewData) override { Data = NewData; }
};
