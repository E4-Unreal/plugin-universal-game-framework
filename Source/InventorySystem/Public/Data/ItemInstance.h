// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Data/DataInstanceBase.h"
#include "Interfaces/ItemInstanceInterface.h"
#include "ItemInstance.generated.h"

/**
 *
 */
UCLASS(EditInlineNew)
class INVENTORYSYSTEM_API UItemInstance : public UDataInstanceBase, public IItemInstanceInterface
{
    GENERATED_BODY()

protected:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ClampMin = "1"), Replicated)
    int32 Quantity = 1;

public:
    /* Object */

    virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;

    /* ItemInstanceInterface */

    virtual UDataAsset* GetData_Implementation() const override { return Data; }
    virtual int32 GetQuantity_Implementation() const override { return Quantity; }
    virtual void SetData_Implementation(UDataAsset* NewData) override { Data = NewData; }
    virtual void SetQuantity_Implementation(int32 NewQuantity) override { Quantity = NewQuantity; }
};
