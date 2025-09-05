// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "WeaponSlotIndex.generated.h"

USTRUCT(BlueprintType)
struct WEAPONMANAGER_API FWeaponSlotIndex
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FGameplayTag Type;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 Index;

    bool Equals(const FWeaponSlotIndex& Other) const { return Type == Other.Type && Index == Other.Index; }
    bool operator==(const FWeaponSlotIndex& Other) const { return Equals(Other); }
    bool operator!=(const FWeaponSlotIndex& Other) const { return !(*this == Other); }
    friend uint32 GetTypeHash(const FWeaponSlotIndex& WeaponSlotIndex) { return FCrc::MemCrc32(&WeaponSlotIndex, sizeof(FWeaponSlotIndex)); }
};
