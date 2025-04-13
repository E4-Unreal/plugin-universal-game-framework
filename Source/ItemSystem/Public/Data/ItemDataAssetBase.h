// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "ItemDataAssetBase.generated.h"

/**
 *
 */
UCLASS(Abstract)
class ITEMSYSTEM_API UItemDataAssetBase : public UPrimaryDataAsset
{
    GENERATED_BODY()

protected:
    UPROPERTY(VisibleDefaultsOnly, Category = "State")
    bool bValid = true;

public:
    UFUNCTION(BlueprintPure)
    virtual FORCEINLINE bool IsValid() const { return bValid; }

    UFUNCTION(BlueprintPure)
    FORCEINLINE bool IsNotValid() const { return !IsValid(); }

    virtual bool SetData(int32 ID, FTableRowBase* Row) { return true; }
};
