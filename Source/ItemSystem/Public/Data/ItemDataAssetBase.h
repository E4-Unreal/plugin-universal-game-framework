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
    UPROPERTY(EditDefaultsOnly, Category = "Config", meta = (ClampMin = 0))
    int32 ID;

private:
    UPROPERTY(VisibleDefaultsOnly, Category = "State", meta = (DisplayName = 0))
    bool bValid = true;

public:
    UFUNCTION(BlueprintPure)
    virtual FORCEINLINE bool IsValid() const { return bValid; }

    UFUNCTION(BlueprintPure)
    FORCEINLINE bool IsNotValid() const { return !IsValid(); }

protected:
    void Update(int32 NewID, FTableRowBase* NewRow);
    virtual void SetData(FTableRowBase* NewRow);
};
