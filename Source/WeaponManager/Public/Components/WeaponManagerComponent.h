// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Types/WeaponSlot.h"
#include "Components/ActorComponent.h"
#include "WeaponManagerComponent.generated.h"


UCLASS(meta=(BlueprintSpawnableComponent))
class WEAPONMANAGER_API UWeaponManagerComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    // TMap<SlotType, MaxNum>
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
    TMap<FGameplayTag, int32> SlotConfig;

protected:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State", Transient)
    TArray<FWeaponSlot> Slots;

public:
    UWeaponManagerComponent();

    /* ActorComponent */

    virtual void InitializeComponent() override;

protected:
    /* API */

    virtual void CreateSlots();
};
