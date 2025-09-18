// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "UGFItemDataTableRow.generated.h"

USTRUCT(BlueprintType)
struct UNIVERSALGAMEFRAMEWORK_API FUGFItemDataTableRow : public FTableRowBase
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
    FText DisplayName;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
    FText Description;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config", meta = (MustImplement = "DataInstanceInterface"))
    TSubclassOf<UObject> DataInstanceClass;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
    TSoftObjectPtr<UStaticMesh> StaticMesh;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
    TSoftObjectPtr<USkeletalMesh> SkeletalMesh;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
    TSoftObjectPtr<UTexture2D> ThumbnailTexture;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config", meta = (ClampMin = 1))
    int32 MaxStack;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config", meta = (Categories = "Item"))
    FGameplayTag ItemType;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config", meta = (Categories = "Currency"))
    FGameplayTag CurrencyType;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
    int32 BuyPrice;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
    int32 SellPrice;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
    FGameplayTag SlotType;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config", meta = (MustImplement = "WeaponActorInterface"))
    TSubclassOf<AActor> ActorClass;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
    FName ActiveSocketName;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
    FName InActiveSocketName;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
    float MaxDurability;
};
