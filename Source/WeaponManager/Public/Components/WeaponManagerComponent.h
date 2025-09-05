// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Types/WeaponSlot.h"
#include "Types/WeaponSlotIndex.h"
#include "Components/ReplicatedComponent.h"
#include "WeaponManagerComponent.generated.h"


UCLASS(meta=(BlueprintSpawnableComponent))
class WEAPONMANAGER_API UWeaponManagerComponent : public UReplicatedComponent
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

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State", Transient, Replicated)
    TArray<FWeaponSlot> Slots;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State", Transient)
    FWeaponSlotIndex CurrentSlotIndex;

public:
    UWeaponManagerComponent();

    /* Object */

    virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;

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

    UFUNCTION(BlueprintPure)
    virtual bool DoesSocketExist(FName SocketName) const;

    UFUNCTION(BlueprintPure)
    virtual bool DoesEmptySlotExist(FGameplayTag SlotType) const;

    UFUNCTION(BlueprintPure)
    virtual bool CanAddWeaponFromData(const TSoftObjectPtr<UDataAsset>& NewData) const;

    UFUNCTION(BlueprintCallable, BlueprintAuthorityOnly)
    void AddWeaponFromData(const TSoftObjectPtr<UDataAsset>& NewData);

protected:
    /* API */

    virtual void CreateSlots();
    virtual void FindMesh();
    virtual bool AttachWeaponActorToSocket(AActor* WeaponActor, const FName SocketName) const;

    virtual AActor* SpawnActorFromData(const TSoftObjectPtr<UDataAsset>& Data) { return SpawnActorFromInstance(CreateInstance(Data)); }
    virtual AActor* SpawnActorFromInstance(UReplicatedObject* Instance);
    virtual UReplicatedObject* CreateInstance(const TSoftObjectPtr<UDataAsset>& Data);
    bool CheckActor(AActor* Actor);
    bool CheckActorClass(TSubclassOf<AActor> ActorClass);
    bool CheckInstance(UReplicatedObject* Instance);
    bool CheckInstanceClass(TSubclassOf<UReplicatedObject> InstanceClass);
    bool CheckData(const TSoftObjectPtr<UDataAsset>& Data) const;
};
