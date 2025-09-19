// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Data/DataInstanceBase.h"
#include "Interfaces/WeaponInstanceInterface.h"
#include "WeaponInstance.generated.h"

class IWeaponDataInterface;

/**
 *
 */
UCLASS()
class WEAPONMANAGER_API UWeaponInstance : public UDataInstanceBase, public IWeaponInstanceInterface
{
    GENERATED_BODY()

protected:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State", Transient, Replicated)
    TWeakObjectPtr<AActor> Actor;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State", Transient, Replicated)
    int32 Durability;

public:
    /* Object */

    virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;

    /* DataInstanceInterface */

    virtual void SetData_Implementation(UDataAsset* NewData) override;

    /* WeaponInstanceInterface */

    virtual float GetDurability_Implementation() const override { return Durability; }
    virtual AActor* GetActor_Implementation() const override { return Actor.Get(); }
    virtual void SetDurability_Implementation(float NewDurability) override;
    virtual void SetActor_Implementation(AActor* NewActor) override { Actor = NewActor; }
};
