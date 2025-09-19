// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DeveloperSettings.h"
#include "InventorySystemSettings.generated.h"

/**
 *
 */
UCLASS(config = UniversalGameFramework, meta = (DisplayName = "InventorySystem", ToolTip = "Settings for InventorySystem"))
class INVENTORYSYSTEM_API UInventorySystemSettings : public UDeveloperSettings
{
    GENERATED_BODY()

protected:
    UPROPERTY(Config, EditDefaultsOnly)
    TSoftObjectPtr<UStaticMesh> DefaultItemMesh;

    UPROPERTY(Config, EditDefaultsOnly)
    TSoftObjectPtr<UStaticMesh> DefaultItemPackageMesh;

    UPROPERTY(Config, EditDefaultsOnly, meta = (MustImplement = "ItemActorInterface"))
    TSoftClassPtr<AActor> DefaultItemActorClass;

public:
    UInventorySystemSettings();

    UFUNCTION(BlueprintPure, meta = (DisplayName = "GetInventorySystemSettings"))
    static UInventorySystemSettings* Get() { return GetMutableDefault<UInventorySystemSettings>(); }

    UFUNCTION(BlueprintPure)
    UStaticMesh* GetDefaultItemMesh() const { return DefaultItemMesh.LoadSynchronous(); }

    UFUNCTION(BlueprintPure)
    UStaticMesh* GetDefaultItemPackageMesh() const { return DefaultItemPackageMesh.LoadSynchronous(); }

    UFUNCTION(BlueprintPure)
    TSubclassOf<AActor> GetDefaultItemActorClass() const { return DefaultItemActorClass.LoadSynchronous(); }
};
