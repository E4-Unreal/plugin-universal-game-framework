// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Types/EquipmentSlotIndex.h"
#include "Types/EquipmentSlotConfig.h"
#include "Types/EquipmentSlot.h"
#include "EquipmentManagerComponent.generated.h"


class USocketManagerComponent;
class UDataInstanceBase;

UCLASS(meta = (BlueprintSpawnableComponent))
class EQUIPMENTMANAGER_API UEquipmentManagerComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
    TArray<FEquipmentSlotConfig> SlotConfigs;

protected:
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Reference", Transient)
    TWeakObjectPtr<USocketManagerComponent> SocketManager;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State", Transient)
    TArray<FEquipmentSlot> Slots;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State", Transient)
    TMap<FEquipmentSlotIndex, int32> SlotIndexMap;

public:
    /* ActorComponent */

    virtual void OnRegister() override;

    /* Initialize */

    UFUNCTION(BlueprintCallable, Category = "Initialize")
    virtual void SetSocketManager(USocketManagerComponent* NewSocketManager);

    /* Query */

    UFUNCTION(BlueprintPure)
    virtual bool HasSlot(FEquipmentSlotIndex InSlotIndex) const;

    UFUNCTION(BlueprintPure)
    virtual const FEquipmentSlot& GetSlot(FEquipmentSlotIndex InSlotIndex) const;

    UFUNCTION(BlueprintPure)
    virtual bool IsSlotEmpty(FEquipmentSlotIndex InSlotIndex) const;

    UFUNCTION(BlueprintPure)
    virtual FEquipmentSlotIndex GetEmptySlotIndex(FGameplayTag Type) const;

    UFUNCTION(BlueprintPure)
    virtual UDataInstanceBase* GetEquipment(FEquipmentSlotIndex InSlotIndex) const;

    /* API */

    UFUNCTION(BlueprintPure)
    virtual bool CanEquip(UDataInstanceBase* NewEquipment, FEquipmentSlotIndex InSlotIndex = FEquipmentSlotIndex()) const;

    UFUNCTION(BlueprintCallable)
    virtual void Equip(UDataInstanceBase* NewEquipment, FEquipmentSlotIndex InSlotIndex = FEquipmentSlotIndex());

    UFUNCTION(BlueprintCallable)
    virtual UDataInstanceBase* UnEquip(FEquipmentSlotIndex InSlotIndex);

protected:
    /* Initialize */

    virtual void FindSocketManager();
    virtual void CreateSlots();

    /* API */

    virtual void OnEquip(const FEquipmentSlot& Slot);
    virtual void OnUnEquip(const FEquipmentSlot& Slot);
};
