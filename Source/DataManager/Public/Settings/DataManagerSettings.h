// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DeveloperSettings.h"
#include "DataManagerSettings.generated.h"

/**
 *
 */
UCLASS(config = DataManager, meta = (DisplayName = "DataManager", ToolTip = "Settings for DataManager"))
class DATAMANAGER_API UDataManagerSettings : public UDeveloperSettings
{
    GENERATED_BODY()

public:
    UDataManagerSettings();

    UFUNCTION(BlueprintPure, meta = (DisplayName = "GetDataManagerSettings"))
    static UDataManagerSettings* Get() { return GetMutableDefault<UDataManagerSettings>(); }
};
