// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Types/ItemDefinitionData.h"
#include "ItemDefinition.generated.h"

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

public:
#if WITH_EDITOR
    UFUNCTION(BlueprintCallable)
    virtual bool SetData(const FItemDefinitionData& InData);
#endif
};
