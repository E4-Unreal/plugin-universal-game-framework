// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WeaponSlotIndex.h"
#include "WeaponSlot.generated.h"

class IWeaponDataInterface;
class IWeaponInstanceInterface;

USTRUCT(BlueprintType)
struct WEAPONMANAGER_API FWeaponSlot
{
    GENERATED_BODY()

    static const FWeaponSlot EmptySlot;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FWeaponSlotIndex Index;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TScriptInterface<IWeaponInstanceInterface> WeaponInstance;

    FORCEINLINE bool IsEmpty() const { return WeaponInstance == nullptr; }

    TScriptInterface<IWeaponDataInterface> GetData() const;
    void SetData(const TScriptInterface<IWeaponDataInterface>& NewData);

    const FName GetActiveSocketName() const;
    const FName GetInActiveSocketName() const;

    AActor* GetActor() const;
    void SetActor(AActor* NewActor);

    bool operator==(const FWeaponSlotIndex& Other) const { return Index == Other; }
    bool operator!=(const FWeaponSlotIndex& Other) const { return !(*this == Other); }
};
