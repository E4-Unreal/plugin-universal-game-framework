// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "DataAssetBuilder.generated.h"

/**
 *
 */
UCLASS(Abstract, Blueprintable)
class DATAMANAGER_API UDataAssetBuilder : public UObject
{
    GENERATED_BODY()

protected:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config", meta = (MustImplement = "DataInterface"))
    TSoftClassPtr<UDataAsset> DataClass;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
    TSoftObjectPtr<UDataTable> DataTable;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
    FName Prefix = "DA";

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
    FName DataName;

public:
    /* Query */

    UFUNCTION(BlueprintPure)
    FORCEINLINE TSubclassOf<UDataAsset> GetDataClass() const { return DataClass.LoadSynchronous(); }

    UFUNCTION(BlueprintPure)
    FORCEINLINE UDataTable* GetDataTable() const { return DataTable.LoadSynchronous(); }

    UFUNCTION(BlueprintPure)
    FORCEINLINE FName GetPrefix() const { return Prefix; }

    UFUNCTION(BlueprintPure)
    FName GetDataName() const;

    /* API */

    virtual bool UpdateData(UDataAsset* Data, FTableRowBase* TableRow) { return false; }
};
