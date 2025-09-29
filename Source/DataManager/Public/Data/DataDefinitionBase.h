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
    int32 ID;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config", meta = (DisplayPriority = 1))
    FText DisplayName;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config", meta = (DisplayPriority = 2))
    FText Description;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config", meta = (DisplayPriority = 3, MustImplement = "DataObjectInterface"))
    TSubclassOf<UObject> DataObjectClass;

public:
    /* DataDefinitionInterface */

    virtual int32 GetID_Implementation() const override { return ID; }
    virtual void SetID_Implementation(int32 NewID) override { ID = NewID; }
    virtual FText GetDisplayName_Implementation() const override { return DisplayName; }
    virtual void SetDisplayName_Implementation(const FText& NewDisplayName) override { DisplayName = NewDisplayName; }
    virtual FText GetDescription_Implementation() const override { return Description; }
    virtual void SetDescription_Implementation(const FText& NewDescription) override { Description = NewDescription; }
    virtual UDataAsset* GetDataByInterface_Implementation(TSubclassOf<UInterface> InterfaceClass) const override;
    virtual UObject* CreateDataObject_Implementation() const override;
};
