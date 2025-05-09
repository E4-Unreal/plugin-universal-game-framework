// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EditorUtilityObject.h"
#include "DefinitionGenerator.generated.h"

class UDefinitionBase;

/**
 *
 */
UCLASS()
class DYNAMICDATAEDITOR_API UDefinitionGenerator : public UEditorUtilityObject
{
    GENERATED_BODY()

protected:
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Config")
    FString Path = "/Game/Project/Data/";

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Config")
    FString Prefix = "DA_";

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Config")
    TMap<TSubclassOf<UDefinitionBase>, TObjectPtr<UDataTable>> DefinitionDataTableMap;

protected:
    UFUNCTION(BlueprintCallable)
    void Update();

    UDefinitionBase* GetOrCreateDefinition(TSubclassOf<UDefinitionBase> DefinitionClass, int32 ID) const;

    void UpdateDefinitionFromDataTable(TSubclassOf<UDefinitionBase> DefinitionClass, UDataTable* DataTable);

    void UpdateDefinition(UDefinitionBase* Definition, FTableRowBase* Row);

    virtual void OnUpdateDefinition(UDefinitionBase* Definition, FTableRowBase* Row) {}

    FString GetPath(TSubclassOf<UDefinitionBase> DefinitionClass) const;
    FString GetPrefix(TSubclassOf<UDefinitionBase> DefinitionClass) const;
};
