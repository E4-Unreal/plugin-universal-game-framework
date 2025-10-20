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
    int32 ID;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowedClasses = "SocketDataInterface"))
    TObjectPtr<UDataAsset> SocketDefinition;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowedClasses = "SocketDataInterface"), Instanced)
    TObjectPtr<UDataAsset> SocketDefinitionInstance;

    FSocketSlotConfig() { }

    FSocketSlotConfig(FGameplayTag InSocketType)
    {
        SocketType = InSocketType;
    }

    FSocketSlotConfig(FGameplayTag InSocketType, FName InSocketName)
    {
        SocketType = InSocketType;
        SocketName = InSocketName;
    }

    bool IsValid() const { return SocketType.IsValid(); }
};
