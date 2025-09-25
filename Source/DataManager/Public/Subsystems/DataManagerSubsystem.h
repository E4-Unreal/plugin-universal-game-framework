// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/EngineSubsystem.h"
#include "DataManagerSubsystem.generated.h"

/**
 *
 */
UCLASS()
class DATAMANAGER_API UDataManagerSubsystem : public UEngineSubsystem
{
    GENERATED_BODY()

public:
    /* Subsystem */

    virtual bool ShouldCreateSubsystem(UObject* Outer) const override;

    /* API */

    UFUNCTION(BlueprintPure)
    virtual UDataAsset* GetDataAsset(FName AssetType, int32 ID) const;

    UFUNCTION(BlueprintPure)
    virtual TArray<UDataAsset*> GetDataAssets(FName AssetType) const;

    UFUNCTION(BlueprintPure)
    virtual TMap<int32, UDataAsset*> GetDataAssetMap(FName AssetType) const;
};
