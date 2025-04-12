// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DeveloperSettings.h"
#include "ItemSystemSettings.generated.h"

class UItemDatabase;

/**
 *
 */
UCLASS()
class ITEMSYSTEM_API UItemSystemSettings : public UDeveloperSettings
{
    GENERATED_BODY()

protected:
    UPROPERTY(Config, EditDefaultsOnly, Category = "Settings")
    TSoftObjectPtr<UItemDatabase> ItemDatabase;

public:
    UItemSystemSettings();

    UFUNCTION(BlueprintPure, meta = (DisplayName = "GetItemSystemSettings"))
    static UItemSystemSettings* Get() { return GetMutableDefault<UItemSystemSettings>(); }

    UFUNCTION(BlueprintPure)
    UItemDatabase* GetItemDatabase() const;
};
