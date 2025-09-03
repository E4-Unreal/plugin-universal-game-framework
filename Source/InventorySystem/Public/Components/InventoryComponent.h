// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Types/ItemInstance.h"
#include "Types/InventorySlot.h"
#include "InventoryComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FUGFInventoryUpdatedSignature, int32, SlotIndex);

class IItemDataInterface;

UCLASS(meta = (BlueprintSpawnableComponent))
class INVENTORYSYSTEM_API UInventoryComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config", meta = (ClampMin = 1))
    int32 MaxSlotNum = 4;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
    TArray<FItemInstance> StartupItems;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config", meta = (MustImplement = "ItemActorInterface"))
    TSubclassOf<AActor> ItemActorClass;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
    FVector DropItemOffset;

    UPROPERTY(BlueprintAssignable, Category = "UI")
    FUGFInventoryUpdatedSignature InventoryUpdated;

protected:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, ReplicatedUsing = OnRep_InventorySlots, Transient, Category = "State")
    TArray<FInventorySlot> InventorySlots;

public:
    UInventoryComponent();

    virtual void BeginPlay() override;
    virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

    UFUNCTION(BlueprintPure)
    bool HasItem(const FItemInstance& NewItem) const;

    UFUNCTION(BlueprintCallable)
    virtual bool AddItem(const FItemInstance& NewItem);

    UFUNCTION(BlueprintCallable)
    virtual bool RemoveItem(const FItemInstance& NewItem);

    UFUNCTION(BlueprintCallable)
    virtual bool SetInventorySlotQuantity(int32 SlotIndex, int32 NewQuantity);

    UFUNCTION(BlueprintCallable)
    virtual bool SetInventorySlot(const FInventorySlot& NewInventorySlot);

    UFUNCTION(BlueprintCallable)
    virtual void RemoveInventorySlot(int32 SlotIndex);

    UFUNCTION(BlueprintCallable, Category = "UI")
    virtual void SwapOrFillInventorySlots(int32 SourceIndex, int32 DestinationIndex, UInventoryComponent* OtherInventoryComponent = nullptr);

    UFUNCTION(BlueprintPure)
    virtual bool IsSlotEmpty(int32 SlotIndex) { return !InventorySlots.FindByKey(SlotIndex); }

    UFUNCTION(BlueprintCallable)
    virtual void DropItemFromSlot(int32 SlotIndex, int32 Quantity);

    /* Getter */

    // 현재 아이템 보유 수량
    UFUNCTION(BlueprintPure)
    virtual int32 GetItemQuantity(const TScriptInterface<IItemDataInterface>& Item) const;

    // 현재 추가 가능한 아이템 수량
    UFUNCTION(BlueprintPure)
    virtual int32 GetItemCapacity(const TScriptInterface<IItemDataInterface>& Item) const;

    UFUNCTION(BlueprintPure, Category = "UI")
    virtual const FInventorySlot& GetInventorySlot(int32 Index) const;

protected:
    virtual void AddDefaultItems();

    UFUNCTION()
    virtual void OnRep_InventorySlots(const TArray<FInventorySlot>& OldInventorySlots);
};
