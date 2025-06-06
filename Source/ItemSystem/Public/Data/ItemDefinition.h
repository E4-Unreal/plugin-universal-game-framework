﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InstancedStruct.h"
#include "ItemDefinition.generated.h"

struct FItemDataTableRow;

/**
 * 프로젝트 전용 ItemDefinition 클래스 작성이 필요합니다.
 * DefaultItemDefinition 참조
 */
UCLASS(Abstract)
class ITEMSYSTEM_API UItemDefinition : public UPrimaryDataAsset
{
    GENERATED_BODY()

    static const FInstancedStruct EmptyData;

protected:
    UPROPERTY(EditDefaultsOnly, BlueprintGetter = GetID, Category = "Config", meta = (ClampMin = 0))
    int32 ID;

    UPROPERTY(EditDefaultsOnly, BlueprintGetter = GetDisplayText, Category = "Config")
    FText DisplayText;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Config", meta = (BaseStruct = "/Script/Engine.TableRowBase"))
    TArray<FInstancedStruct> DataList;

    UPROPERTY(VisibleDefaultsOnly, Category = "State")
    bool bValid = true;

public:
    void Update(int32 NewID, UScriptStruct* RowStruct, FTableRowBase* TableRow);
    void Reset();

protected:
    virtual void OnUpdate(UScriptStruct* RowStruct, FTableRowBase* TableRow);
    virtual void UpdateDataList(UScriptStruct* RowStruct, FTableRowBase* TableRow);
    virtual void OnReset();

public:
    UFUNCTION(BlueprintGetter)
    FORCEINLINE int32 GetID() const { return ID; }

    UFUNCTION(BlueprintGetter)
    const FORCEINLINE FText& GetDisplayText() const { return DisplayText; }

    UFUNCTION(BlueprintPure)
    virtual FORCEINLINE bool IsValid() const { return bValid; }

    UFUNCTION(BlueprintPure)
    FORCEINLINE bool IsNotValid() const { return !IsValid(); }

    UFUNCTION(BlueprintCallable)
    virtual void CheckValid();

    UFUNCTION(BlueprintPure)
    bool HasData(const UScriptStruct* StructType) const;

    template<typename T = UScriptStruct>
    bool HasData()
    {
        return HasData(T::StaticStruct());
    }

    UFUNCTION(BlueprintPure)
    const FInstancedStruct& GetData(const UScriptStruct* StructType) const;

    template<typename T = UScriptStruct>
    const T& GetData()
    {
        return GetData(T::StaticStruct()).template Get<T>();
    }

protected:
    UFUNCTION(BlueprintCallable)
    void SetData(const FInstancedStruct& Value);

    template<typename T = UScriptStruct>
    void SetData(const T& Value)
    {
        FInstancedStruct InstancedStruct = FInstancedStruct::Make(Value);
        SetData(InstancedStruct);
    }
};
