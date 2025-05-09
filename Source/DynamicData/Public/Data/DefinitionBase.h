// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "InstancedStruct.h"
#include "DefinitionBase.generated.h"

/**
 *
 */
UCLASS(Abstract)
class DYNAMICDATA_API UDefinitionBase : public UPrimaryDataAsset
{
    GENERATED_BODY()

    static const FInstancedStruct EmptyData;

protected:
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Config", meta = (ClampMin = 0))
    int32 ID;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Config")
    FText DisplayText;

    UPROPERTY(EditDefaultsOnly, Category = "Config", meta = (BaseStruct = "/Script/Engine.TableRowBase"))
    TArray<FInstancedStruct> DataList;

public:
    virtual FPrimaryAssetId GetPrimaryAssetId() const override;

    FORCEINLINE int32 GetID() const { return ID; }
    FORCEINLINE void SetID(int32 NewID) { ID = NewID; }

    const FORCEINLINE FText& GetDisplayText() const { return DisplayText; }
    FORCEINLINE void SetDisplayText(const FText& NewDisplayText) { DisplayText = NewDisplayText; }

    UFUNCTION(BlueprintPure)
    bool HasData(const UScriptStruct* StructType) const;

    template<typename T = UScriptStruct>
    bool HasData() const
    {
        return HasData(T::StaticStruct());
    }

    UFUNCTION(BlueprintPure)
    const FInstancedStruct& GetData(const UScriptStruct* StructType) const;

    template<typename T = UScriptStruct>
    const T& GetData() const
    {
        return GetData(T::StaticStruct()).template Get<T>();
    }

    void SetData(const FInstancedStruct& Value);

    template<typename T = UScriptStruct>
    void SetData(const T& Value)
    {
        FInstancedStruct InstancedStruct = FInstancedStruct::Make(Value);
        SetData(InstancedStruct);
    }

    void ResetData() { DataList.Reset(); }
};
