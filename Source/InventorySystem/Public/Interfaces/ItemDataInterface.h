// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "UObject/Interface.h"
#include "ItemDataInterface.generated.h"

UINTERFACE(MinimalAPI, Blueprintable, BlueprintType)
class UItemDataInterface : public UInterface
{
    GENERATED_BODY()
};

/**
 *
 */
class INVENTORYSYSTEM_API IItemDataInterface
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
    int32 GetMaxStack() const;

    UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
    FGameplayTag GetItemType() const;

    UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
    TSoftObjectPtr<UStaticMesh> GetStaticMesh() const;

    UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
    TSoftObjectPtr<USkeletalMesh> GetSkeletalMesh() const;

    UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "UI")
    FText GetDisplayName() const;

    UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "UI")
    TSoftObjectPtr<UTexture2D> GetThumbnailTexture() const;
};
