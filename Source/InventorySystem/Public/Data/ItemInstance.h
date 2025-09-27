// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Data/DataObjectBase.h"
#include "Interfaces/ItemObjectInterface.h"
#include "ItemInstance.generated.h"

/**
 *
 */
UCLASS(EditInlineNew)
class INVENTORYSYSTEM_API UItemInstance : public UDataObjectBase, public IItemObjectInterface
{
    GENERATED_BODY()

protected:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ClampMin = "1"), Replicated)
    int32 Quantity = 1;

public:
    /* Object */

    virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;

    /* ItemInstanceInterface */

    virtual int32 GetQuantity_Implementation() const override { return Quantity; }
    virtual void SetQuantity_Implementation(int32 NewQuantity) override { Quantity = NewQuantity; }
};
