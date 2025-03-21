// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Types/UGFItemDefinitionData.h"
#include "UGFItemDefinition.generated.h"

class UUGFItemConfig;

/**
 *
 */
UCLASS(BlueprintType, Blueprintable, Const)
class UGFITEMSYSTEM_API UUGFItemDefinition : public UPrimaryDataAsset
{
    GENERATED_BODY()

    UPROPERTY(EditDefaultsOnly)
    FUGFItemDefinitionData Data;

public:
    UFUNCTION(BlueprintCallable)
    void SetData(const FUGFItemDefinitionData& InData) { Data = InData; }

    UFUNCTION(BlueprintPure)
    const FORCEINLINE FText& GetDisplayName() const { return Data.DisplayName; }

    UFUNCTION(BlueprintPure)
    FORCEINLINE int32 GetMaxStack() const { return Data.MaxStack; }

    template<typename T>
    const T* FindItemConfigByClass(TSubclassOf<T> ItemConfigClass) const;
};
