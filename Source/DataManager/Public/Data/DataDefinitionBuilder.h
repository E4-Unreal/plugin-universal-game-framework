// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "DataDefinitionBuilder.generated.h"

#define SET_TEXT(OldText, NewText) if (!OldText.EqualTo(NewText)) { OldText = NewText; bDirty = true; }
#define SET_DATA(OldData, NewData) if (OldData != NewData) { OldData = NewData; bDirty = true; }

struct FDataDefinitionTableRowBase;
class UDataDefinitionBase;

/**
 *
 */
UCLASS(Abstract, Blueprintable)
class DATAMANAGER_API UDataDefinitionBuilder : public UObject
{
    GENERATED_BODY()

protected:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config", meta = (MustImplement = "DataInterface"))
    TSoftClassPtr<UDataDefinitionBase> DefinitionClass;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
    TSoftObjectPtr<UDataTable> DataTable;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
    FName Prefix = "DA";

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
    FName DataName;

public:
    /* Query */

    UFUNCTION(BlueprintPure)
    TSet<int32> GetIDSet() const;

    UFUNCTION(BlueprintPure)
    FORCEINLINE TSubclassOf<UDataDefinitionBase> GetDefinitionClass() const { return DefinitionClass.LoadSynchronous(); }

    UFUNCTION(BlueprintPure)
    FString GetDataName() const;

    UFUNCTION(BlueprintPure)
    FString GetAssetPath() const;

    UFUNCTION(BlueprintPure)
    FString GetAssetName(int32 ID) const;

    /* API */

    bool UpdateData(UDataDefinitionBase* Definition, int32 ID);

protected:
    /* API */

    static int32 ConvertRowNameToID(FName RowName);

    virtual bool OnUpdateData(UDataDefinitionBase* Definition, FDataDefinitionTableRowBase* DataDefinitionTableRow) { return false; }
};
