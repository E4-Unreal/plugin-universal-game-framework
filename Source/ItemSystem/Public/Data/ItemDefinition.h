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

    UFUNCTION(BlueprintPure)
    const UItemConfig* GetItemConfigByClass(const TSubclassOf<UItemConfig> ItemConfigClass);

    UFUNCTION(BlueprintPure)
    const UItemConfig* GetItemConfigByInterface(const TSubclassOf<UInterface> Interface);

    bool Update(int32 ID, FItemDataTableRow* Row, const TArray<TSubclassOf<UItemConfig>>& ItemConfigClasses);

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

protected:
    virtual bool OnUpdate(int32 ID, FItemDataTableRow* Row);
};
