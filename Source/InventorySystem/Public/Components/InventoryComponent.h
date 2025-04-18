// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Types/InventoryItem.h"
#include "Types/InventorySlot.h"
#include "InventoryComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FUGFInventoryUpdatedSignature, int32, SlotIndex);

class IInventoryItemDataInterface;

UCLASS(meta = (BlueprintSpawnableComponent))
class INVENTORYSYSTEM_API UInventoryComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    UPROPERTY(BlueprintAssignable, Category = "UI")
    FUGFInventoryUpdatedSignature InventoryUpdated;

protected:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config", meta = (ClampMin = 0))
    int32 MaxSlotNum = 4;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
    TArray<FInventoryItem> DefaultItems;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, ReplicatedUsing = OnRep_InventorySlots, Transient, Category = "State")
    TArray<FInventorySlot> InventorySlots;

public:
    UInventoryComponent();

    virtual void BeginPlay() override;
    virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

    UFUNCTION(BlueprintPure)
    bool HasItem(const TScriptInterface<IInventoryItemDataInterface>& Item, int32 Quantity = 1) const;

    UFUNCTION(BlueprintCallable)
    virtual bool AddItem(const TScriptInterface<IInventoryItemDataInterface>& Item, int32 Quantity);

    UFUNCTION(BlueprintCallable)
    virtual bool RemoveItem(const TScriptInterface<IInventoryItemDataInterface>& Item, int32 Quantity);

    UFUNCTION(BlueprintCallable)
    virtual bool SetInventorySlotQuantity(int32 SlotIndex, int32 NewQuantity);

    UFUNCTION(BlueprintCallable)
    virtual bool SetInventorySlot(const FInventorySlot& NewInventorySlot);

    UFUNCTION(BlueprintCallable)
    virtual void RemoveInventorySlot(int32 SlotIndex);

    UFUNCTION(BlueprintCallable, Category = "UI")
    virtual void SwapOrFillInventorySlots(int32 SourceIndex, int32 DestinationIndex);

    /* Getter */

    // 현재 아이템 보유 수량
    UFUNCTION(BlueprintPure)
    int32 GetItemQuantity(const TScriptInterface<IInventoryItemDataInterface>& Item) const;

    // 현재 추가 가능한 아이템 수량
    UFUNCTION(BlueprintPure)
    int32 GetItemCapacity(const TScriptInterface<IInventoryItemDataInterface>& Item) const;

    UFUNCTION(BlueprintPure, Category = "UI")
    FORCEINLINE int32 GetMaxSlotNum() const { return MaxSlotNum; }

    UFUNCTION(BlueprintPure, Category = "UI")
    const FInventorySlot& GetInventorySlot(int32 Index) const;

protected:
    virtual void AddDefaultItems();

    static bool IsValidItem(const TScriptInterface<IInventoryItemDataInterface>& Item, int32 Quantity);
    static const FInventoryItemData GetInventoryItemData(const TScriptInterface<IInventoryItemDataInterface>& Item);

    UFUNCTION()
    virtual void OnRep_InventorySlots(const TArray<FInventorySlot>& OldInventorySlots);
};
