// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/EngineSubsystem.h"
#include "DataAssetRegistrySubsystem.generated.h"

class UDataAssetRegistry;
/**
 *
 */
UCLASS()
class DATAMANAGER_API UDataAssetRegistrySubsystem : public UEngineSubsystem
{
    GENERATED_BODY()

public:
    /* Subsystem */

    virtual bool ShouldCreateSubsystem(UObject* Outer) const override;

    /* API */

    UFUNCTION(BlueprintCallable)
    TSoftObjectPtr<UDataAsset> GetDataByClass(TSubclassOf<UDataAsset> DataAssetClass, int32 ID) const;

    UFUNCTION(BlueprintCallable)
    TSoftObjectPtr<UDataAsset> GetDataByInterface(TSubclassOf<UInterface> InterfaceClass, int32 ID) const;
};
