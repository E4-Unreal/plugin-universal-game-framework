// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Editor/Blutility/Classes/AssetActionUtility.h"
#include "ItemDatabaseAssetAction.generated.h"

class UItemDatabase;
class UItemDefinition;

/**
 *
 */
UCLASS()
class ITEMSYSTEMEDITOR_API UItemDatabaseAssetAction : public UAssetActionUtility
{
    GENERATED_BODY()

public:
    UItemDatabaseAssetAction();

    UFUNCTION(CallInEditor)
    void HardUpdate();

    UFUNCTION(CallInEditor)
    void SoftUpdate();

protected:
    UFUNCTION(BlueprintCallable)
    void Update(UItemDatabase* ItemDatabase);

    UFUNCTION(BlueprintCallable)
    void DeleteAllItemDefinitions(UItemDatabase* ItemDatabase);

    UFUNCTION(BlueprintCallable)
    UItemDefinition* GetOrCreateItemDefinition(UItemDatabase* ItemDatabase, int32 ID);

    static bool CheckRowName(FName RowName, int32& ID);
    static FString GetAssetName(UItemDatabase* ItemDatabase, int32 ID);
    static FString GetPackageName(UItemDatabase* ItemDatabase, int32 ID);
};
