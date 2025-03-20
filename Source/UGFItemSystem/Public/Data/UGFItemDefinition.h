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

    UPROPERTY(EditDefaultsOnly, BlueprintGetter = GetMaxStack, meta = (ClampMin = 1))
    int32 MaxStack = 1;

public:
    UFUNCTION(BlueprintGetter)
    const FText& GetDisplayName() const { return DisplayName; }

    UFUNCTION(BlueprintGetter)
    int32 GetMaxStack() const { return MaxStack; }

    template<typename T>
    const T* FindItemConfigByClass(TSubclassOf<T> ItemConfigClass) const;
};
