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

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
    TArray<FEquipmentSlotConfig> SlotConfigs;

protected:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State", Transient)
    TMap<FGameplayTag, int32> SlotNumMap;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State", Transient)
    TArray<FEquipmentSlot> Slots;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State", Transient)
    TObjectPtr<AActor> SelectedWeapon;

public:
    UEquipmentManagerComponent();

    /* ActorComponent */

    virtual void InitializeComponent() override;

    /* API */

    UFUNCTION(BlueprintPure)
    FORCEINLINE int32 GetSlotNum(FGameplayTag EquipmentType) { return SlotNumMap.Contains(EquipmentType) ? SlotNumMap[EquipmentType] : 0; }

    UFUNCTION(BlueprintPure)
    FORCEINLINE AActor* GetSelectedWeapon() const { return SelectedWeapon; }

    UFUNCTION(BlueprintCallable)
    virtual void SelectWeapon(int32 Index = 0);

    UFUNCTION(BlueprintPure)
    bool HasSlot(FGameplayTag EquipmentType, int32 Index = 0) const;

    UFUNCTION(BlueprintPure)
    const FEquipmentSlot& GetSlot(FGameplayTag EquipmentType, int32 Index = 0) const;

    UFUNCTION(BlueprintCallable)
    virtual bool AddEquipmentToSlot(AActor* NewEquipment, FGameplayTag EquipmentType, int32 Index = 0);

    UFUNCTION(BlueprintCallable)
    virtual AActor* RemoveEquipmentFromSlot(FGameplayTag EquipmentType, int32 Index = 0);

protected:
    void CreateSlots();

    virtual AActor* SpawnActorByData(UDataAsset* Data);

    FEquipmentSlot& GetSlotRef(FGameplayTag EquipmentType, int32 Index = 0) const { return *const_cast<FEquipmentSlot*>(&GetSlot(EquipmentType, Index)); }
};
