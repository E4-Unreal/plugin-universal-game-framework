// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ItemDataAssetBase.h"
#include "Types/ItemDefinitionData.h"
#include "ItemDefinition.generated.h"

class UItemConfig;

/**
 *
 */
UCLASS()
class ITEMSYSTEM_API UItemDefinition : public UItemDataAssetBase
{
    GENERATED_BODY()

    friend class UItemDatabase;

protected:
    UPROPERTY(EditDefaultsOnly, Category = "Config", meta = (ShowOnlyInnerProperties))
    FItemDefinitionData Data;

    UPROPERTY(EditDefaultsOnly, Category = "Config")
    TArray<TObjectPtr<UItemConfig>> ItemConfigs;

public:
    UFUNCTION(BlueprintPure)
    const FORCEINLINE FItemDefinitionData& GetData() const { return Data; }

    UFUNCTION(BlueprintPure)
    const UItemConfig* GetItemConfigByClass(const TSubclassOf<UItemConfig> ItemConfigClass);

    UFUNCTION(BlueprintPure)
    const UItemConfig* GetItemConfigByInterface(const TSubclassOf<UInterface> Interface);

    template<typename T = UItemConfig>
    T* GetItemConfigByClass() const
    {
        return Cast<T>(GetItemConfigByClass(T::StaticClass()));
    }

    template<typename T = UInterface>
    UItemConfig* GetItemConfigByInterface() const
    {
        return GetItemConfigByInterface(T::StaticClass());
    }
};
