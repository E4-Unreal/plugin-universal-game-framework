// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "ItemDatabase.generated.h"

class UItemConfig;
class UItemDefinition;
struct FItemDataTableRow;

/**
 * ItemDataTable을 통해 ItemDefinition 데이터 에셋을 생성하거나 업데이트합니다.
 */
UCLASS()
class ITEMSYSTEM_API UItemDatabase : public UPrimaryDataAsset
{
    GENERATED_BODY()

protected:
    UPROPERTY(EditDefaultsOnly, Category = "Config")
    FString Directory = "/Game/Project/Data/Item/ItemDefinitions/";

    UPROPERTY(EditDefaultsOnly, Category = "Config")
    FString Prefix = "DA_ID_";

    UPROPERTY(EditDefaultsOnly, Category = "Config")
    TObjectPtr<UDataTable> ItemDataTable;

    UPROPERTY(EditDefaultsOnly, Category = "Config")
    TArray<TSubclassOf<UItemConfig>> ItemConfigClasses;

    UPROPERTY(VisibleDefaultsOnly, Category = "State")
    TMap<int32, TObjectPtr<UItemDefinition>> ItemDefinitionMap;

public:
    UFUNCTION(BlueprintCallable)
    virtual void HardUpdate();

    UFUNCTION(BlueprintCallable)
    virtual UItemDefinition* GetItemDefinitionByID(int32 ID);

protected:
    UFUNCTION(BlueprintPure)
    static bool CheckRowName(FName RowName, int32& ID);

    UFUNCTION(BlueprintPure)
    FString GetAssetName(int32 ID) const;

    UFUNCTION(BlueprintPure)
    FString GetPackageName(int32 ID) const;

    UFUNCTION(BlueprintPure)
    UItemDefinition* CreateItemDefinition(int32 ID) const;

    UFUNCTION(BlueprintCallable)
    virtual void Update();

    UFUNCTION(BlueprintCallable)
    void DeleteAllItemDefinitions();
};
