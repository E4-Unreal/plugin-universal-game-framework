// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ItemConfig.h"
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

    UPROPERTY(EditDefaultsOnly, Category = "Config")
    TArray<TObjectPtr<UItemConfig>> ItemConfigs;

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

    template<typename T>
    T* GetItemConfigByClass(TSubclassOf<T> ItemConfigClass) const
    {
        if (ItemConfigClass == nullptr || !ItemConfigClass->IsChildOf(UItemConfig::StaticClass())) return nullptr;

        for (auto ItemConfig : ItemConfigs)
        {
            if (ItemConfig && ItemConfig->IsA(ItemConfigClass))
            {
                return Cast<T>(ItemConfig);
            }
        }

        return nullptr;
    }

protected:
    virtual bool OnUpdate(int32 ID, FItemDataTableRow* Row);
};
