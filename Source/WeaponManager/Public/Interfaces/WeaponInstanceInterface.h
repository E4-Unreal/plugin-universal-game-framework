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
    TScriptInterface<IWeaponDataInterface> GetData() const;

    UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
    void SetData(const TScriptInterface<IWeaponDataInterface>& NewData);

    UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
    AActor* GetActor() const;

    UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
    void SetActor(AActor* NewActor);

    UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
    float GetDurability() const;

    UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
    void SetDurability(float NewDurability);
};
