// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UGFItemInstance.h"
#include "Interfaces/WeaponInstanceInterface.h"
#include "UGFEquipmentInstance.generated.h"

/**
 *
 */
UCLASS()
class UNIVERSALGAMEFRAMEWORK_API UUGFEquipmentInstance : public UUGFItemInstance,
    public IWeaponInstanceInterface
{
    GENERATED_BODY()

protected:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config", Transient, Replicated)
    TWeakObjectPtr<AActor> Actor;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config", Transient, Replicated)
    int32 Durability;

public:
    /* Object */

    virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;

    /* DataInstanceBase */

    virtual void SetData(UDataAsset* NewData) override;

    /* WeaponInstanceInterface */

    virtual float GetDurability_Implementation() const override { return Durability; }
    virtual AActor* GetActor_Implementation() const override { return Actor.Get(); }
    virtual void SetDurability_Implementation(float NewDurability) override;
    virtual void SetActor_Implementation(AActor* NewActor) override { Actor = NewActor; }
};
