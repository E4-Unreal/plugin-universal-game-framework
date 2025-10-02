// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "DataDefinitionBase.generated.h"

class UDataInstanceBase;
/**
 *
 */
UCLASS(Abstract)
class DATAMANAGER_API UDataDefinitionBase : public UPrimaryDataAsset
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

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config", meta = (DisplayPriority = 4))
    TSubclassOf<UDataInstanceBase> DataInstanceClass;

public:
    UDataDefinitionBase();

    /* Object */

    virtual FPrimaryAssetId GetPrimaryAssetId() const override;

    /* API */

    UFUNCTION(BlueprintPure)
    virtual UDataAsset* GetDataByInterface(TSubclassOf<UInterface> InterfaceClass) const;

    template <typename TInterface = UInterface>
    UDataAsset* GetDataByInterface() const
    {
        return GetDataByInterface(TInterface::StaticClass());
    }

    UFUNCTION(BlueprintPure)
    virtual UDataInstanceBase* CreateDataInstance() const;
};
