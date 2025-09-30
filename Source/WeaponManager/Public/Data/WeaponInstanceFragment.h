// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Data/Flexible/DataInstanceFragment.h"
#include "Interfaces/WeaponInstanceInterface.h"
#include "WeaponInstanceFragment.generated.h"

/**
 *
 */
UCLASS()
class WEAPONMANAGER_API UWeaponInstanceFragment : public UDataInstanceFragment, public IWeaponInstanceInterface
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config", Transient, Replicated)
    TWeakObjectPtr<AActor> Actor;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config", Transient, Replicated, meta = (ClampMin = 0))
    float Durability;

public:
    /* Object */

    virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;

    /* WeaponInstanceInterface */

    virtual float GetDurability_Implementation() const override { return Durability; }
    virtual AActor* GetActor_Implementation() const override { return Actor.Get(); }
    virtual void SetDurability_Implementation(float NewDurability) override { Durability = NewDurability; }
    virtual void SetActor_Implementation(AActor* NewActor) override { Actor = NewActor; }
};
