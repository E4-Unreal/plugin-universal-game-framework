// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SocketManagerComponent.h"
#include "Types/EquipmentSlot.h"
#include "Types/EquipmentSlotConfig.h"
#include "Types/EquipmentSlotIndex.h"
#include "EquipmentManagerComponent.generated.h"


UCLASS(meta = (BlueprintSpawnableComponent))
class EQUIPMENTMANAGER_API UEquipmentManagerComponent : public USocketManagerComponent
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
    TArray<FEquipmentSlotConfig> SlotConfigs;

protected:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State", Transient)
    TArray<FEquipmentSlot> Slots;

public:
    UEquipmentManagerComponent();

    /* ActorComponent */

    virtual void InitializeComponent() override;

    /* API */

    UFUNCTION(BlueprintPure)
    bool HasSlot(const FEquipmentSlotIndex& SlotIndex) const;

    UFUNCTION(BlueprintPure)
    const FEquipmentSlot& GetSlot(const FEquipmentSlotIndex& SlotIndex) const;

    UFUNCTION(BlueprintCallable)
    virtual bool AddEquipmentToSlot(const TScriptInterface<IEquipmentInterface>& NewEquipment, const FEquipmentSlotIndex& SlotIndex);

    UFUNCTION(BlueprintCallable)
    virtual TScriptInterface<IEquipmentInterface> RemoveEquipmentFromSlot(const FEquipmentSlotIndex& SlotIndex);

protected:
    void CreateSlots();

    FEquipmentSlot& GetSlotRef(const FEquipmentSlotIndex& SlotIndex) const { return *const_cast<FEquipmentSlot*>(&GetSlot(SlotIndex)); }
};
