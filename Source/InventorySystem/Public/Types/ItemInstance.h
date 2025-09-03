// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interfaces/ItemDataInterface.h"
#include "ItemInstance.generated.h"

USTRUCT(Atomic, BlueprintType)
struct INVENTORYSYSTEM_API FItemInstance
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TScriptInterface<IItemDataInterface> Data;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ClampMin = "1"))
    int32 Quantity = 1;

    bool IsValid() const { return Data && Quantity > 0; }

    int32 GetMaxStack() const;
    int32 GetCapacity() const;
    FGameplayTag GetItemType() const;

    bool operator==(const FItemInstance& Other) const { return Data == Other.Data && Quantity == Other.Quantity; }
    bool operator!=(const FItemInstance& Other) const { return !(*this == Other); }

    bool operator==(const TScriptInterface<IItemDataInterface>& Other) const { return Data == Other; }
    bool operator!=(const TScriptInterface<IItemDataInterface>& Other) const { return !(*this == Other); }
};
