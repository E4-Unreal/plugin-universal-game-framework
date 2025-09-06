// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Types/QuickSlot.h"
#include "Interfaces/QuickSlotManagerInterface.h"
#include "QuickSlotManagerComponent.generated.h"

class USocketManagerComponent;

UCLASS(meta = (BlueprintSpawnableComponent))
class QUICKSLOTMANAGER_API UQuickSlotManagerComponent : public UActorComponent, public IQuickSlotManagerInterface
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
    int32 SlotNum;

    /*UPROPERTY(BlueprintAssignable)
    FSlotIndexChangedDelegate SlotIndexChangedDelegate;

    UPROPERTY(BlueprintAssignable)
    FSlotUpdatedDelegate SlotUpdatedDelegate;*/

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

    /* QuickSlotManagerInterface */

    /*virtual int32 GetSlotNum_Implementation() const override { return SlotNum; }
    virtual bool IsSlotEmpty_Implementation(int32 InSlotIndex) const override { return GetSlot(InSlotIndex).IsEmpty(); }
    virtual TScriptInterface<ISlotDataInterface> GetSlotData_Implementation(int32 InSlotIndex) const override { return GetSlot(InSlotIndex).Data; }
    virtual void SwapSlots_Implementation(int32 SourceIndex, int32 DestinationIndex) override;
    virtual void BindSlotIndexChangedHandler_Implementation(const FSlotIndexChangedHandler& Handler) override { SlotIndexChangedDelegate.Add(Handler); }
    virtual void UnBindSlotIndexChangedHandler_Implementation(const FSlotIndexChangedHandler& Handler) override { SlotIndexChangedDelegate.Remove(Handler); }
    virtual void BindSlotUpdatedHandler_Implementation(const FSlotUpdatedHandler& Handler) override { SlotUpdatedDelegate.Add(Handler); }
    virtual void UnBindSlotUpdatedHandler_Implementation(const FSlotUpdatedHandler& Handler) override { SlotUpdatedDelegate.Remove(Handler); }*/

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
    virtual void SetSlotByData(int32 InSlotIndex, const TScriptInterface<IQuickSlotDataInterface>& NewData);

protected:
    virtual void CreateSlots();
    virtual void FindSocketManager();
    virtual void OnSlotIndexChanged(int32 OldSlotIndex);
};
