// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DataManager/Public/Data/ReplicatedObject.h"
#include "Interfaces/WeaponInstanceInterface.h"
#include "WeaponInstance.generated.h"

class IWeaponDataInterface;

/**
 *
 */
UCLASS()
class WEAPONMANAGER_API UWeaponInstance : public UReplicatedObject, public IWeaponInstanceInterface
{
    GENERATED_BODY()

protected:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State", Transient)
    TScriptInterface<IWeaponDataInterface> Data;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State", Transient)
    TWeakObjectPtr<AActor> Actor;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State", Transient)
    int32 Durability;

public:
    /* WeaponDataInstanceInterface */

    virtual TScriptInterface<IWeaponDataInterface> GetData_Implementation() const override { return Data; }
    virtual void SetData_Implementation(const TScriptInterface<IWeaponDataInterface>& NewData) override { Data = NewData; }
    virtual AActor* GetActor_Implementation() const override { return Actor.Get(); }
    virtual void SetActor_Implementation(AActor* NewActor) override { Actor = NewActor; }
    virtual float GetDurability_Implementation() const override { return Durability; }
    virtual void SetDurability_Implementation(float NewDurability) override;
};
