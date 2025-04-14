// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ItemDataAssetBase.h"
#include "InstancedStruct.h"
#include "Types/ItemDataTableRow.h"
#include "ItemDefinition.generated.h"

struct FItemDataTableRow;
class UItemConfig;

/**
 *
 */
UCLASS(Const)
class ITEMSYSTEM_API UItemDefinition : public UItemDataAssetBase
{
    GENERATED_BODY()

    static const FInstancedStruct EmptyData;

protected:
    UPROPERTY(EditDefaultsOnly, BlueprintGetter = GetID, Category = "Config", meta = (ClampMin = 0))
    int32 ID;

    UPROPERTY(EditDefaultsOnly, BlueprintGetter = GetDisplayText, Category = "Config")
    FText DisplayText;

    UPROPERTY(EditDefaultsOnly, Category = "Config")
    TArray<TObjectPtr<UItemConfig>> ItemConfigs;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Config", meta = (BaseStruct = "TableRowBase"))
    TArray<FInstancedStruct> DataList;

public:
    /* ItemDataAssetBase */

    virtual bool IsValid() const override;

    /* ItemDefinition */

    UFUNCTION(BlueprintPure)
    const FInstancedStruct& GetData(const UScriptStruct* StructType = nullptr) const;

    UFUNCTION(BlueprintCallable)
    void SetData(const FInstancedStruct& Value);

    UFUNCTION(BlueprintPure)
    UItemConfig* GetItemConfigByClass(const TSubclassOf<UItemConfig> ItemConfigClass);

    UFUNCTION(BlueprintPure)
    UItemConfig* GetItemConfigByInterface(const TSubclassOf<UInterface> Interface);

    template<typename T = UScriptStruct>
    const T& GetData()
    {
        return GetData(T::StaticStruct()).template Get<T>();
    }

    template<typename T = UScriptStruct>
    void SetData(const T& Value)
    {
        FInstancedStruct InstancedStruct = FInstancedStruct::Make(Value);
        SetData(InstancedStruct);
    }

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
    /* ItemDataAssetBase */

    virtual void OnUpdate(FTableRowBase* TableRow) override;
    virtual void OnReset() override;

    /* ItemDefinition */

    UItemConfig* GetOrCreateItemConfig(TSubclassOf<UItemConfig> ItemConfigClass);

    template<typename T = UItemConfig>
    T* GetOrCreateItemConfig()
    {
        return Cast<T>(GetOrCreateItemConfig(T::StaticClass()));
    }

    virtual void UpdateItemConfigs(FTableRowBase* TableRow);

public:
    /* Getter */

    UFUNCTION(BlueprintGetter)
    FORCEINLINE int32 GetID() const { return ID; }

    FORCEINLINE void SetID(int32 Value) { ID = Value; }

    UFUNCTION(BlueprintGetter)
    const FORCEINLINE FText& GetDisplayText() const { return DisplayText; }
};
