// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "EquipmentSlotConfig.generated.h"

USTRUCT(BlueprintType)
struct EQUIPMENTMANAGER_API FEquipmentSlotConfig
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FGameplayTag Type;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TArray<FGameplayTag> SocketTags;
};
