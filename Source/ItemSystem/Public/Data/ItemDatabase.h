// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ItemDefinition.h"
#include "Engine/DataAsset.h"
#include "ItemDatabase.generated.h"

class UItemDefinition;

/**
 * ItemDataTable을 통해 ItemDefinition 데이터 에셋을 생성하거나 업데이트합니다.
 */
UCLASS()
class ITEMSYSTEM_API UItemDatabase : public UPrimaryDataAsset
{
    GENERATED_BODY()

    friend class UItemDatabaseAssetAction;

protected:
    UPROPERTY(EditDefaultsOnly, Category = "Config")
    FString Path = "/Game/Project/Data/Item/ItemDefinitions/";

    UPROPERTY(EditDefaultsOnly, Category = "Config")
    FString Prefix = "DA_ID_";

    UPROPERTY(EditDefaultsOnly, Category = "Config")
    TObjectPtr<UDataTable> ItemDataTable;

    UPROPERTY(EditDefaultsOnly, Category = "Config")
    TSubclassOf<UItemDefinition> ItemDefinitionClass = UItemDefinition::StaticClass();

    UPROPERTY(VisibleDefaultsOnly, Category = "State")
    TMap<int32, TObjectPtr<UItemDefinition>> ItemDefinitionMap;

public:
    UFUNCTION(BlueprintCallable)
    virtual UItemDefinition* GetItemDefinitionByID(int32 ID);
};
