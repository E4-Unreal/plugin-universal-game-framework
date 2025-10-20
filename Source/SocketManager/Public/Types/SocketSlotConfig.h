// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "SocketSlotConfig.generated.h"

USTRUCT(BlueprintType)
struct SOCKETMANAGER_API FSocketSlotConfig
{
    GENERATED_BODY()

    static const FSocketSlotConfig EmptySlotConfig;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (Categories = "Socket"))
    FGameplayTag SocketType;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FName SocketName;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ClampMin = 0))
    int32 ID = 0;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowedClasses = "SocketDataInterface"))
    TSoftObjectPtr<UDataAsset> SocketDefinition;

    FSocketSlotConfig() { }

    FSocketSlotConfig(FGameplayTag InSocketType, int32 InID = 0)
    {
        SocketType = InSocketType;
        ID = InID;
    }

    FSocketSlotConfig(FGameplayTag InSocketType, FName InSocketName, int32 InID = 0)
    {
        SocketType = InSocketType;
        SocketName = InSocketName;
        ID = InID;
    }

    bool IsValid() const { return SocketType.IsValid(); }
};
