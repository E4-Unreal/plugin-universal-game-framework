// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "WeaponSlotIndex.h"
#include "WeaponSlot.generated.h"

class IWeaponActorInterface;
class IWeaponDataInterface;

USTRUCT(BlueprintType)
struct WEAPONMANAGER_API FWeaponSlot
{
    GENERATED_BODY()

    static const FWeaponSlot EmptySlot;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FGameplayTag Type;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 Index;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TScriptInterface<IWeaponDataInterface> Data;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TObjectPtr<AActor> Actor;

    FORCEINLINE bool IsEmpty() const { return Actor == nullptr; }

    const FName GetActiveSocketName() const;
    const FName GetInActiveSocketName() const;

    bool operator==(const FWeaponSlotIndex& Other) const { return Type == Other.Type && Index == Other.Index; }
    bool operator!=(const FWeaponSlotIndex& Other) const { return !(*this == Other); }
};
