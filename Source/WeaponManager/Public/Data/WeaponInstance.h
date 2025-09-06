// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interfaces/WeaponInstanceInterface.h"
#include "Objects/SlotContent.h"
#include "WeaponInstance.generated.h"

class IWeaponDataInterface;

/**
 *
 */
UCLASS()
class WEAPONMANAGER_API UWeaponInstance : public USlotContent, public IWeaponInstanceInterface
{
    GENERATED_BODY()

protected:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State", Transient, Replicated)
    int32 Durability;

public:
    /* Object */

    virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;

    /* WeaponDataInstanceInterface */

    virtual UDataAsset* GetData_Implementation() const override { return Data; }
    virtual float GetDurability_Implementation() const override { return Durability; }
    virtual void SetData_Implementation(UDataAsset* NewData) override;
    virtual void SetDurability_Implementation(float NewDurability) override;
};
