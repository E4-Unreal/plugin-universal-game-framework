// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Types/WeaponSlot.h"
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
    int32 CurrentIndex;

public:
    UWeaponManagerComponent();

    /* ActorComponent */

    virtual void InitializeComponent() override;

    /* API */

    UFUNCTION(BlueprintCallable)
    FORCEINLINE void SetMesh(USkeletalMeshComponent* NewMesh) { Mesh = NewMesh; }

    UFUNCTION(BlueprintPure)
    AActor* GetCurrentWeaponActor() const;

    UFUNCTION(BlueprintCallable, Server, Reliable)
    void SetSlotIndex(FWeaponSlotIndex NewSlotIndex, bool bForce = false);

    UFUNCTION(BlueprintPure)
    virtual bool CanAddWeaponFromData(const TSoftObjectPtr<UDataAsset>& NewData) const;

    UFUNCTION(BlueprintCallable, BlueprintAuthorityOnly)
    void AddWeaponFromData(const TSoftObjectPtr<UDataAsset>& NewData);

protected:
    /* SlotManagerComponentBase */

    virtual void CreateSlots() override;
    virtual int32 GetMaxSlotNum() const override { return MaxSlotNum; }

    /* API */

    virtual int32 GetIndex(const FWeaponSlotIndex& SlotIndex);

    virtual void FindMesh();

    virtual bool DoesSocketExist(FName SocketName) const;
    virtual bool DoesEmptySlotExist(FGameplayTag SlotType) const;

    virtual bool AttachWeaponActorToSocket(AActor* WeaponActor, const FName SocketName) const;
    virtual AActor* SpawnActorFromData(const TSoftObjectPtr<UDataAsset>& Data) { return SpawnActorFromInstance(CreateInstance(Data)); }
    virtual AActor* SpawnActorFromInstance(USlotContent* Instance);
    virtual USlotContent* CreateInstance(const TSoftObjectPtr<UDataAsset>& Data);
    bool CheckActor(AActor* Actor) const;
    static bool CheckActorClass(TSubclassOf<AActor> ActorClass);
    bool CheckInstance(USlotContent* Instance) const;
    static bool CheckInstanceClass(TSubclassOf<USlotContent> InstanceClass);
    bool CheckData(const TSoftObjectPtr<UDataAsset>& Data) const;
};
