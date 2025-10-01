// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Types/WeaponSlotIndex.h"
#include "Components/SlotManagerComponentBase.h"
#include "WeaponManagerComponent.generated.h"


UCLASS(meta=(BlueprintSpawnableComponent))
class WEAPONMANAGER_API UWeaponManagerComponent : public USlotManagerComponentBase
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
    int32 MaxSlotNum;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State", Transient)
    TMap<FWeaponSlotIndex, int32> SlotIndexMap;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State", Transient)
    int32 CurrentSlotIndex;

public:
    UWeaponManagerComponent();

    /* ActorComponent */

    virtual void InitializeComponent() override;

    /* SlotManagerComponentBase */

    virtual int32 GetEmptySlotIndex(UDataInstanceBase* NewContent) const override;

    /* API */

    UFUNCTION(BlueprintCallable)
    FORCEINLINE void SetMesh(USkeletalMeshComponent* NewMesh) { Mesh = NewMesh; }

    UFUNCTION(BlueprintPure)
    AActor* GetCurrentWeaponActor() const;

    UFUNCTION(BlueprintCallable, Server, Reliable)
    void SetWeaponSlotIndex(FWeaponSlotIndex NewWeaponSlotIndex, bool bForce = false);

    UFUNCTION(BlueprintCallable, Server, Reliable)
    void SetSlotIndex(int32 NewSlotIndex, bool bForce = false);

protected:
    /* SlotManagerComponentBase */

    virtual void CreateSlots() override;
    virtual bool CheckData(UDataAsset* Data) const override;
    virtual void HandleOnSlotUpdated(int32 Index) override;

    /* SlotManagerInterface */

    virtual int32 GetMaxSlotNum_Implementation() const override { return MaxSlotNum; }

    /* API */

    virtual int32 GetIndex(const FWeaponSlotIndex& SlotIndex);

    virtual void FindMesh();

    virtual bool DoesSocketExist(FName SocketName) const;

    virtual bool AttachWeaponActorToSocket(AActor* WeaponActor, const FName SocketName) const;
    virtual AActor* SpawnActorFromData(UDataAsset* Data);
    virtual AActor* SpawnActorFromContent(UDataInstanceBase* Content);
    bool CheckActor(AActor* Actor) const;
    static bool CheckActorClass(TSubclassOf<AActor> ActorClass);

    virtual void Equip(UDataInstanceBase* Content);
    virtual void UnEquip(UDataInstanceBase* Content);
};
