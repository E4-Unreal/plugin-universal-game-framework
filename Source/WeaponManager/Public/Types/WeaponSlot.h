// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "WeaponSlot.generated.h"

class IWeaponActorInterface;
class IWeaponDataInterface;

USTRUCT(BlueprintType)
struct WEAPONMANAGER_API FWeaponSlot
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FGameplayTag Type;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 Index;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TScriptInterface<IWeaponDataInterface> Data;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TScriptInterface<IWeaponActorInterface> Actor;

    FORCEINLINE bool IsEmpty() const { return Actor == nullptr; }
};
