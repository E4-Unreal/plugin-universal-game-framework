// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "ItemConfig.generated.h"

class UItemDefinition;
struct FItemDataTableRow;

/**
 *
 */
UCLASS(Abstract, DefaultToInstanced, EditInlineNew, CollapseCategories)
class ITEMSYSTEM_API UItemConfig : public UPrimaryDataAsset
{
    GENERATED_BODY()

protected:
    UPROPERTY(VisibleDefaultsOnly, Category = "State")
    bool bValid = true;

public:
    UFUNCTION(BlueprintPure)
    FORCEINLINE bool IsValid() const { return bValid; }

    UFUNCTION(BlueprintPure)
    FORCEINLINE bool IsNotValid() const { return !IsValid(); }

    bool Update(UItemDefinition* ItemDefinition, FItemDataTableRow* Row);

protected:
    virtual bool OnUpdate(UItemDefinition* ItemDefinition, FItemDataTableRow* Row);
};
