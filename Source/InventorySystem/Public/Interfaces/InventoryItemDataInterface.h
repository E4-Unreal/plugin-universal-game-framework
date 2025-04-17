// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "InventoryItemDataInterface.generated.h"

struct FInventoryItemData;

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UInventoryItemDataInterface : public UInterface
{
    GENERATED_BODY()
};

/**
 *
 */
class INVENTORYSYSTEM_API IInventoryItemDataInterface
{
    GENERATED_BODY()

    // Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
    UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
    const FInventoryItemData& GetInventoryItemData() const;
    virtual const FInventoryItemData& GetInventoryItemData_Implementation() const;

    UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
    bool Equip();
    virtual bool Equip_Implementation() const;

    UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
    bool UnEquip();
    virtual bool UnEquip_Implementation() const;

    UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
    bool Use();
    virtual bool Use_Implementation() const;
};
