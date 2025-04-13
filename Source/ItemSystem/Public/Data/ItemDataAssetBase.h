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

private:
    UPROPERTY(VisibleDefaultsOnly, Category = "State", meta = (DisplayPriority = 0))
    bool bValid = true;

public:
    UFUNCTION(BlueprintPure)
    virtual FORCEINLINE bool IsValid() const { return bValid; }

    UFUNCTION(BlueprintPure)
    FORCEINLINE bool IsNotValid() const { return !IsValid(); }

    void Update(FTableRowBase* TableRow);

    void Reset();

protected:
    virtual void OnUpdate(FTableRowBase* TableRow);

    virtual void OnReset();
};
