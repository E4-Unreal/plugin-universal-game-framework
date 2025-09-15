// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "DataAssetRegistry.generated.h"

class UDataAssetBuilder;
/**
 *
 */
UCLASS()
class DATAMANAGER_API UDataAssetRegistry : public UPrimaryDataAsset
{
    GENERATED_BODY()

protected:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
    TSoftObjectPtr<UDataTable> DataTableToBuild;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
    TSubclassOf<UDataAssetBuilder> BuilderClass;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State")
    TSoftObjectPtr<UDataTable> DataTable;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State")
    TSubclassOf<UDataAsset> DataClass;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State")
    TMap<int32, TSoftObjectPtr<UDataAsset>> DataMap;

public:
    /* API */

    UFUNCTION(BlueprintPure)
    TSubclassOf<UDataAsset> GetDataClass() const { return DataClass; }

    UFUNCTION(BlueprintPure)
    bool Implements(TSubclassOf<UInterface> InterfaceClass) const { return DataClass && DataClass->ImplementsInterface(InterfaceClass); }

    UFUNCTION(BlueprintPure)
    bool IsChildOf(TSubclassOf<UDataAsset> InDataClass) const { return DataClass && DataClass->IsChildOf(InDataClass); }

    UFUNCTION(BlueprintCallable)
    virtual TSoftObjectPtr<UDataAsset> GetDataByID(int32 ID) const { return DataMap.FindRef(ID); }
};
