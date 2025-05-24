// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SocketManagerComponent.h"
#include "Types/EquipmentSlot.h"
#include "Types/EquipmentSlotConfig.h"
#include "EquipmentManagerComponent.generated.h"


UCLASS(meta = (BlueprintSpawnableComponent))
class EQUIPMENTMANAGER_API UEquipmentManagerComponent : public USocketManagerComponent
{
    GENERATED_BODY()

protected:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
    TArray<FEquipmentSlotConfig> SlotConfigs;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State", Transient)
    TArray<FEquipmentSlot> Slots;

public:
    UEquipmentManagerComponent();

    /* ActorComponent */

    virtual void PostInitProperties() override;

    /* API */

    UFUNCTION(BlueprintPure)
    bool HasSlot(const FGameplayTag& EquipmentType, const int32 Index = 0) const;

    UFUNCTION(BlueprintPure)
    const FEquipmentSlot& GetSlot(const FGameplayTag& EquipmentType, const int32 Index = 0) const;

    UFUNCTION(BlueprintCallable)
    virtual bool AddEquipmentToSlot(const TScriptInterface<IEquipmentInterface>& NewEquipment, const FGameplayTag& EquipmentType, int32 Index);

    UFUNCTION(BlueprintCallable)
    virtual TScriptInterface<IEquipmentInterface> RemoveEquipmentFromSlot(const FGameplayTag& EquipmentType, int32 Index);

protected:
    void CreateSlots();

    FEquipmentSlot& GetSlotRef(const FGameplayTag& EquipmentType, const int32 Index = 0) const { return *const_cast<FEquipmentSlot*>(&GetSlot(EquipmentType, Index)); }
};
