// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Components/ActorComponent.h"
#include "Types/SocketSlot.h"
#include "Types/SocketSlotConfig.h"
#include "SocketManagerComponent.generated.h"


class ISocketDataInterface;

UCLASS(meta = (BlueprintSpawnableComponent))
class SOCKETMANAGER_API USocketManagerComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
    TArray<FSocketSlotConfig> SlotConfigs;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
    FName DataAssetType;

protected:
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Reference", Transient)
    TWeakObjectPtr<UMeshComponent> RootMesh;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State", Transient)
    TArray<FSocketSlot> Slots;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State", Transient)
    TArray<TObjectPtr<UStaticMeshComponent>> StaticMeshComponentPool;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State", Transient)
    TArray<TObjectPtr<USkeletalMeshComponent>> SkeletalMeshComponentPool;

public:
    USocketManagerComponent();

    virtual void OnRegister() override;

    /* Initialize */

    UFUNCTION(BlueprintCallable)
    virtual void SetRootMesh(UMeshComponent* NewRootMesh);

    /* API */

    UFUNCTION(BlueprintCallable)
    virtual void ResetSlot(FGameplayTag InSocketType);

    UFUNCTION(BlueprintCallable, meta = (Categories = "Socket"))
    virtual UStaticMeshComponent* SetSocketByStaticMesh(UStaticMesh* NewStaticMesh, FGameplayTag SocketType, FName SocketName, FGameplayTagContainer SocketTypesToHide = FGameplayTagContainer());

    UFUNCTION(BlueprintCallable, meta = (Categories = "Socket"))
    virtual USkeletalMeshComponent* SetSocketBySkeletalMesh(USkeletalMesh* NewSkeletalMesh, FGameplayTag SocketType, FName SocketName, FGameplayTagContainer SocketTypesToHide = FGameplayTagContainer());

    UFUNCTION(BlueprintCallable, meta = (Categories = "Socket"))
    virtual AActor* SetSocketByActorClass(TSubclassOf<AActor> NewActorClass, FGameplayTag SocketType, FName SocketName, FGameplayTagContainer SocketTypesToHide = FGameplayTagContainer());

    UFUNCTION(BlueprintCallable)
    virtual void SetSocketByData(const TScriptInterface<ISocketDataInterface>& NewData);

    UFUNCTION(BlueprintCallable, meta = (Categories = "Socket"))
    virtual void SetSocketByID(int32 NewID);

    UFUNCTION(BlueprintCallable, meta = (Categories = "Socket"))
    virtual void SetMaterial(FGameplayTag SocketType, UMaterialInterface* Material, int32 Index = 0);

    UFUNCTION(BlueprintCallable, meta = (Categories = "Socket"))
    virtual void SetMaterialByName(FGameplayTag SocketType, UMaterialInterface* Material, FName SlotName);

protected:
    /* Initialize */

    virtual void FindRootMesh();
    virtual void CreateSlots();
    virtual void ResetSlots();
    virtual void CheckPools();

    /* API */

    virtual bool CheckData(const TScriptInterface<ISocketDataInterface>& InData) const;

    virtual bool HasSlot(FGameplayTag InSocketType) const;
    virtual const FSocketSlot& GetSlot(FGameplayTag InSocketType) const;
    virtual FSocketSlot& GetSlotRef(FGameplayTag InSocketType);
    virtual void ClearSlot(FGameplayTag InSocketType);

    virtual bool DoesSocketExist(FName InSocketName) const;
    virtual bool IsModular(USkeletalMesh* InSkeletalMesh) const;

    virtual UStaticMeshComponent* GetOrCreateStaticMeshComponent();
    virtual void ReleaseStaticMeshComponent(UStaticMeshComponent* StaticMeshComponent);
    virtual USkeletalMeshComponent* GetOrCreateSkeletalMeshComponent();
    virtual void ReleaseSkeletalMeshComponent(USkeletalMeshComponent* SkeletalMeshComponent);
    virtual AActor* SpawnActor(TSubclassOf<AActor> InActorClass);

    virtual const FSocketSlotConfig& GetSlotConfig(FGameplayTag InSocketType) const;
    virtual FName GetDefaultSocketName(FGameplayTag SocketType) const;
    virtual UDataAsset* GetDefaultData(FGameplayTag SocketType) const;
    virtual UDataAsset* GetDataByID(int32 ID) const;

    virtual void ShowSockets(FGameplayTag HiddenBySocketType, const FGameplayTagContainer& SocketTypesToHide);
    virtual void HideSockets(FGameplayTag HiddenBySocketType, const FGameplayTagContainer& SocketTypesToHide);
};
