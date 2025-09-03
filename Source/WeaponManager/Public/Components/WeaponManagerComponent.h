// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Types/WeaponSlot.h"
#include "Types/WeaponSlotIndex.h"
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
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Reference", Transient)
    TWeakObjectPtr<USkeletalMeshComponent> Mesh;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State", Transient)
    TArray<FWeaponSlot> Slots;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State", Transient)
    FWeaponSlotIndex CurrentSlotIndex;

public:
    UWeaponManagerComponent();

    /* ActorComponent */

    virtual void InitializeComponent() override;

    /* API */

    UFUNCTION(BlueprintCallable)
    virtual bool AddWeaponByData(const TScriptInterface<IWeaponDataInterface>& NewWeaponData);

protected:
    /* API */

    virtual void CreateSlots();
    virtual AActor* SpawnWeaponActor(TSubclassOf<AActor> WeaponActorClass) const;
    virtual bool AttachWeaponActorToSocket(AActor* WeaponActor, const FName SocketName) const;
};
