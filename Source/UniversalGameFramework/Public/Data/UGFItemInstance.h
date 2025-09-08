// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Data/DataInstanceBase.h"
#include "Interfaces/ItemInstanceInterface.h"
#include "Interfaces/WeaponInstanceInterface.h"
#include "UGFItemInstance.generated.h"

/**
 *
 */
UCLASS()
class UNIVERSALGAMEFRAMEWORK_API UUGFItemInstance : public UDataInstanceBase,
    public IItemInstanceInterface,
    public IWeaponInstanceInterface
{
    GENERATED_BODY()

protected:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ClampMin = "1"))
    int32 Quantity = 1;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State", Transient, Replicated)
    TWeakObjectPtr<AActor> Actor;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State", Transient, Replicated)
    int32 Durability;

public:
    /* ItemInstanceInterface */

    virtual int32 GetQuantity_Implementation() const override { return Quantity; }
    virtual void SetQuantity_Implementation(int32 NewQuantity) override { Quantity = NewQuantity; }

    /* Object */

    virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;

    /* SlotContent */

    virtual void SetData_Implementation(UDataAsset* NewData) override;

    /* WeaponDataInstanceInterface */

    virtual float GetDurability_Implementation() const override { return Durability; }
    virtual AActor* GetActor_Implementation() const override { return Actor.Get(); }
    virtual void SetDurability_Implementation(float NewDurability) override;
    virtual void SetActor_Implementation(AActor* NewActor) override { Actor = NewActor; }
};
