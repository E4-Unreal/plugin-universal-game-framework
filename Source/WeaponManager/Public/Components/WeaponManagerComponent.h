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

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
    FWeaponSlotIndex StartupSlotIndex;

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
    virtual void BeginPlay() override;

    /* API */

    UFUNCTION(BlueprintCallable)
    FORCEINLINE void SetMesh(USkeletalMeshComponent* NewMesh) { Mesh = NewMesh; }

    UFUNCTION(BlueprintPure)
    AActor* GetCurrentWeaponActor() const;

    UFUNCTION(BlueprintPure)
    const FWeaponSlot& GetSlotByIndex(FWeaponSlotIndex InSlotIndex) const;

    UFUNCTION(BlueprintCallable)
    virtual void SetSlotIndex(FWeaponSlotIndex NewSlotIndex, bool bForce = false);

    UFUNCTION(BlueprintCallable)
    virtual bool AddWeaponByData(const TScriptInterface<IWeaponDataInterface>& NewWeaponData);

protected:
    /* API */

    virtual void CreateSlots();
    virtual void FindMesh();
    virtual AActor* SpawnWeaponActorByData(const TScriptInterface<IWeaponDataInterface>& WeaponData) const;
    virtual bool AttachWeaponActorToSocket(AActor* WeaponActor, const FName SocketName) const;
};
