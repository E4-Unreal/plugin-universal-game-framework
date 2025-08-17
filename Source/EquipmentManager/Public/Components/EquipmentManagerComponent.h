// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Types/EquipmentSlot.h"
#include "Types/EquipmentSlotConfig.h"
#include "Types/EquipmentSlotIndex.h"
#include "EquipmentManagerComponent.generated.h"


UCLASS(meta = (BlueprintSpawnableComponent))
class EQUIPMENTMANAGER_API UEquipmentManagerComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
    TArray<FEquipmentSlotConfig> SlotConfigs;

protected:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State", Transient)
    TMap<FEquipmentTypeTag, int32> SlotNumMap;

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
    virtual bool AddEquipmentToSlot(const TScriptInterface<IEquipmentActorInterface>& NewEquipment, const FEquipmentSlotIndex& SlotIndex);

    UFUNCTION(BlueprintCallable)
    virtual TScriptInterface<IEquipmentActorInterface> RemoveEquipmentFromSlot(const FEquipmentSlotIndex& SlotIndex);

protected:
    void CreateSlots();

    virtual AActor* SpawnActorByData(UDataAsset* Data);
    virtual AActor* SpawnActorByClass(TSubclassOf<AActor> ActorClass) const;

    FEquipmentSlot& GetSlotRef(const FEquipmentSlotIndex& SlotIndex) const { return *const_cast<FEquipmentSlot*>(&GetSlot(SlotIndex)); }
};
