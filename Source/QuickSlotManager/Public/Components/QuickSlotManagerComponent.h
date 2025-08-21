// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Types/QuickSlot.h"
#include "QuickSlotManagerComponent.generated.h"


class USocketManagerComponent;

UCLASS(meta = (BlueprintSpawnableComponent))
class QUICKSLOTMANAGER_API UQuickSlotManagerComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
    int32 SlotNum;

protected:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Reference", Transient)
    TWeakObjectPtr<USocketManagerComponent> SocketManager;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State", Transient)
    int32 SlotIndex;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State", Transient)
    TArray<FQuickSlot> Slots;

public:
    UQuickSlotManagerComponent(const FObjectInitializer& ObjectInitializer);

    virtual void InitializeComponent() override;

    /* API */

    UFUNCTION(BlueprintPure)
    FORCEINLINE bool HasSlot(int32 InSlotIndex) const { return InSlotIndex >= 0 && InSlotIndex < Slots.Num(); }

    UFUNCTION(BlueprintPure)
    const FORCEINLINE FQuickSlot& GetSlot(int32 InSlotIndex) const { return HasSlot(InSlotIndex) ? Slots[InSlotIndex] : FQuickSlot::EmptySlot; }

    UFUNCTION(BlueprintPure)
    const FORCEINLINE FQuickSlot& GetCurrentSlot() const { return GetSlot(SlotIndex); }

    UFUNCTION(BlueprintCallable)
    virtual void SetSlotIndex(int32 NewSlotIndex);

    UFUNCTION(BlueprintCallable)
    virtual void SetSlot(int32 InSlotIndex, FQuickSlot NewSlot);

protected:
    virtual void CreateSlots();
    virtual void FindSocketManager();
    virtual void OnSlotIndexChanged(int32 OldSlotIndex);
};
