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
    TSubclassOf<UDefinitionBase> DefinitionClass;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Config")
    TObjectPtr<UDataTable> DataTable;

protected:
    UFUNCTION(BlueprintCallable)
    void Update();

    UDefinitionBase* GetOrCreateDefinition(int32 ID) const;

    void UpdateDefinition(UDefinitionBase* Definition, FTableRowBase* Row);

    virtual void OnUpdateDefinition(UDefinitionBase* Definition, FTableRowBase* Row) {}

    FString GetPath() const;
    FString GetPrefix() const;
};
