// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Interfaces/SlotManagerInterface.h"
#include "ShopComponent.generated.h"

struct FCurrency;
class UDataInstanceBase;
class UDataDefinitionBase;
struct FGameplayTag;

USTRUCT(BlueprintType)
struct FProductSlot
{
    GENERATED_BODY()

    static const FProductSlot EmptySlot;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TObjectPtr<UDataDefinitionBase> Definition;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ClampMin = 0))
    int32 Stock;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ClampMin = 0))
    int32 MaxStock;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool bInfiniteStock;

    FProductSlot() { }
};

UCLASS(BlueprintType)
class SHOPSYSTEM_API UProductSlotContainer : public UObject
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 Index;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FProductSlot Slot;
};

UCLASS(meta = (BlueprintSpawnableComponent))
class SHOPSYSTEM_API UShopComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    UPROPERTY(BlueprintAssignable)
    FOnSlotUpdated OnSlotUpdated;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
    TArray<FProductSlot> Slots;

protected:
    // TMap<Index, SlotIndex>
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State", Transient)
    TMap<int32, int32> SlotIndexMap;

public:
    UShopComponent();

    /* ActorComponent */

    virtual void BeginPlay() override;

    /* Query */

    UFUNCTION(BlueprintPure)
    bool IsSlotExist(int32 Index) const { return SlotIndexMap.Contains(Index); }

    UFUNCTION(BlueprintPure)
    TArray<FProductSlot> GetSlots() const;

    UFUNCTION(BlueprintPure)
    const FProductSlot& GetSlot(int32 Index) const;

    /* API */

    UFUNCTION(BlueprintCallable, meta = (DefaultToSelf = "Customer"))
    virtual bool BuyItem(AActor* Customer, int32 Index, int32 Quantity);

    UFUNCTION(BlueprintCallable, meta = (DefaultToSelf = "Customer"))
    virtual bool SellItem(AActor* Customer, UDataDefinitionBase* Item, int32 Quantity);

    UFUNCTION(BlueprintCallable, meta = (DefaultToSelf = "Customer"))
    virtual bool SellEquipment(AActor* Customer, UDataInstanceBase* Equipment);
protected:
    /* API */

    virtual bool CheckDefinition(UDataDefinitionBase* Definition) const;
    virtual bool CheckInstance(UDataInstanceBase* Instance) const;

    // Currency

    virtual bool HasCurrency(AActor* Customer, FCurrency Currency) const;
    virtual bool AddCurrency(AActor* Customer, FCurrency Currency) const;
    virtual bool RemoveCurrency(AActor* Customer, FCurrency Currency) const;

    // Inventory

    virtual bool HasItem(AActor* Customer, UDataDefinitionBase* Item, int32 Quantity) const;
    virtual bool AddItem(AActor* Customer, UDataDefinitionBase* Item, int32 Quantity) const;
    virtual bool RemoveItem(AActor* Customer, UDataDefinitionBase* Item, int32 Quantity) const;
    virtual FCurrency CalculateBuyPrice(UDataDefinitionBase* Item, int32 Quantity) const;
    virtual FCurrency CalculateSellPrice(UDataDefinitionBase* Item, int32 Quantity) const;

    virtual bool HasEquipment(AActor* Customer, UDataInstanceBase* Equipment) const;
    virtual bool RemoveEquipment(AActor* Customer, UDataInstanceBase* Equipment) const;
    virtual FCurrency CalculateEquipmentSellPrice(UDataInstanceBase* Equipment) const;

    // Slot

    virtual void SetStock(int32 Index, int32 NewStock);
};
