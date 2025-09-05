// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "WeaponInstanceInterface.generated.h"

class IWeaponDataInterface;

UINTERFACE(MinimalAPI, Blueprintable, BlueprintType)
class UWeaponInstanceInterface : public UInterface
{
    GENERATED_BODY()
};

/**
 *
 */
class WEAPONMANAGER_API IWeaponInstanceInterface
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
    TScriptInterface<IWeaponDataInterface> GetWeaponData() const;

    UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
    void SetWeaponData(const TScriptInterface<IWeaponDataInterface>& NewWeaponData);

    UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
    float GetDurability() const;

    UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
    void SetDurability(float NewDurability);
};
