// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DeveloperSettings.h"
#include "DataManagerSettings.generated.h"

class UDataAssetRegistry;
/**
 *
 */
UCLASS(config = DataManager, meta = (DisplayName = "DataManager", ToolTip = "Settings for DataManager"))
class DATAMANAGER_API UDataManagerSettings : public UDeveloperSettings
{
    GENERATED_BODY()

protected:
    UPROPERTY(Config, EditDefaultsOnly, Category = "Settings")
    TArray<TSoftObjectPtr<UDataAssetRegistry>> DataAssetRegistries;

public:
    UDataManagerSettings();

    UFUNCTION(BlueprintPure, meta = (DisplayName = "GetDataManagerSettings"))
    static UDataManagerSettings* Get() { return GetMutableDefault<UDataManagerSettings>(); }

    UFUNCTION(BlueprintPure)
    const TArray<TSoftObjectPtr<UDataAssetRegistry>>& GetDataAssetRegistries() const { return DataAssetRegistries; }
};
