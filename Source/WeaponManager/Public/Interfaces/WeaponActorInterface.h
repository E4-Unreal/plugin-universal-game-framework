// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "WeaponActorInterface.generated.h"

class UReplicatedObject;
class IWeaponInstanceInterface;

UINTERFACE(MinimalAPI, Blueprintable, BlueprintType)
class UWeaponActorInterface : public UInterface
{
    GENERATED_BODY()
};

/**
 *
 */
class WEAPONMANAGER_API IWeaponActorInterface
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
    UReplicatedObject* GetInstance() const;

    UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
    void SetInstance(UReplicatedObject* NewInstance);
};
