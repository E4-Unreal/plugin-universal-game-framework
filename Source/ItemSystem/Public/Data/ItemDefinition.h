// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Types/ItemDefinitionData.h"
#include "ItemDefinition.generated.h"

struct FItemDataTableRow;

/**
 *
 */
UCLASS()
class ITEMSYSTEM_API UItemDefinition : public UPrimaryDataAsset
{
    GENERATED_BODY()

protected:
    UPROPERTY(EditDefaultsOnly, Category = "Config", meta = (ShowOnlyInnerProperties))
    FItemDefinitionData Data;

    UPROPERTY(VisibleDefaultsOnly, Category = "State")
    bool bValid = true;

public:
    UFUNCTION(BlueprintPure)
    FORCEINLINE bool IsValid() const { return bValid; }

    UFUNCTION(BlueprintPure)
    FORCEINLINE bool IsNotValid() const { return !IsValid(); }

    UFUNCTION(BlueprintPure)
    const FORCEINLINE FItemDefinitionData& GetData() const { return Data; }

    bool Update(int32 ID, FItemDataTableRow* Row);

protected:
    virtual bool OnUpdate(int32 ID, FItemDataTableRow* Row);
};
