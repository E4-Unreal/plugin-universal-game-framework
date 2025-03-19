// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "UGFItemDefinition.generated.h"

class UUGFItemConfig;

/**
 *
 */
UCLASS(BlueprintType, Blueprintable, Const)
class UGFITEMSYSTEM_API UUGFItemDefinition : public UPrimaryDataAsset
{
    GENERATED_BODY()

    UPROPERTY(EditDefaultsOnly, BlueprintGetter = GetDisplayName, Category = "Config")
    FText DisplayName;

    UPROPERTY(EditDefaultsOnly, Category = "Config")
    TArray<TObjectPtr<UUGFItemConfig>> ItemConfigs;

public:
    UFUNCTION(BlueprintGetter)
    const FText& GetDisplayName() const { return DisplayName; }

    template<typename T>
    const T* FindItemConfigByClass(TSubclassOf<T> ItemConfigClass) const;
};
