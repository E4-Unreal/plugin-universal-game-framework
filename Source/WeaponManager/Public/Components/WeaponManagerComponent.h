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
    virtual bool CanAddWeaponFromData(UDataAsset* NewData) const;

    UFUNCTION(BlueprintCallable, BlueprintAuthorityOnly)
    void AddWeaponFromData(UDataAsset* NewData);

protected:
    /* SlotManagerComponentBase */

    virtual void CreateSlots() override;
    virtual int32 GetMaxSlotNum() const override { return MaxSlotNum; }
    virtual bool CheckContent(USlotContent* Content) const override;
    virtual bool CheckContentClass(TSubclassOf<USlotContent> ContentClass) const override;
    virtual bool CheckData(UDataAsset* Data) const override;

    /* API */

    virtual int32 GetIndex(const FWeaponSlotIndex& SlotIndex);

    virtual void FindMesh();

    virtual bool DoesSocketExist(FName SocketName) const;
    virtual bool DoesEmptySlotExist(FGameplayTag SlotType) const;

    virtual bool AttachWeaponActorToSocket(AActor* WeaponActor, const FName SocketName) const;
    virtual AActor* SpawnActorFromData(UDataAsset* Data) { return SpawnActorFromContent(CreateContentFromData(Data)); }
    virtual AActor* SpawnActorFromContent(USlotContent* Content);
    bool CheckActor(AActor* Actor) const;
    static bool CheckActorClass(TSubclassOf<AActor> ActorClass);
};
