// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Data/DataInstanceBase.h"
#include "Interfaces/ItemInstanceInterface.h"
#include "UGFItemInstance.generated.h"

/**
 *
 */
UCLASS()
class UNIVERSALGAMEFRAMEWORK_API UUGFItemInstance : public UDataInstanceBase,
    public IItemInstanceInterface
{
    GENERATED_BODY()

protected:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config", Transient, Replicated, meta = (ClampMin = "1"))
    int32 Quantity = 1;

public:
    /* Object */

    virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;

    /* ItemInstanceInterface */

    virtual int32 GetQuantity_Implementation() const override { return Quantity; }
    virtual void SetQuantity_Implementation(int32 NewQuantity) override { Quantity = NewQuantity; }
};
