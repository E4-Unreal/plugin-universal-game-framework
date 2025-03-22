// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UGFItemConfig.h"
#include "Engine/DataAsset.h"
#include "Types/UGFItemDefinitionData.h"
#include "UGFItemDefinition.generated.h"

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
    FORCEINLINE int32 GetID() const { return Data.ID; }

    UFUNCTION(BlueprintPure)
    const FORCEINLINE FText& GetDisplayName() const { return Data.DisplayName; }

    UFUNCTION(BlueprintPure)
    virtual bool IsValid() const;

    template<typename T>
    const T* GetItemConfigByClass(TSubclassOf<T> ItemConfigClass) const
    {
        if (ItemConfigClass == nullptr || !ItemConfigClass->IsChildOf(UUGFItemConfig::StaticClass())) return nullptr;

        for (auto ItemConfig : Data.ItemConfigs)
        {
            if (ItemConfig && ItemConfig->IsA(ItemConfigClass))
            {
                return Cast<T>(ItemConfig);
            }
        }

        return nullptr;
    }
};
