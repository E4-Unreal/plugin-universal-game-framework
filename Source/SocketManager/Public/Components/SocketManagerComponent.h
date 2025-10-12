// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Components/ActorComponent.h"
#include "Types/SocketSlot.h"
#include "Types/SocketSlotConfig.h"
#include "SocketManagerComponent.generated.h"


UCLASS(meta = (BlueprintSpawnableComponent))
class SOCKETMANAGER_API USocketManagerComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
    TArray<FSocketSlotConfig> SlotConfigs;

protected:
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Reference", Transient)
    TWeakObjectPtr<UMeshComponent> RootMesh;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State", Transient)
    TArray<FSocketSlot> Slots;

public:
    USocketManagerComponent();

    virtual void OnRegister() override;

    /* Initialize */

    UFUNCTION(BlueprintCallable)
    virtual void SetRootMesh(UMeshComponent* NewRootMesh);

    /* API */

    UFUNCTION(BlueprintCallable)
    virtual void ClearSlot(FGameplayTag InSocketTag);

    UFUNCTION(BlueprintCallable)
    virtual void SetStaticMesh(UStaticMesh* NewStaticMesh, FGameplayTag SocketTag, FName SocketName);

    UFUNCTION(BlueprintCallable)
    virtual void SetSkeletalMesh(USkeletalMesh* NewSkeletalMesh, FGameplayTag SocketTag, bool bModular = true, FName SocketName = NAME_None);

    UFUNCTION(BlueprintCallable)
    virtual AActor* SetActor(TSubclassOf<AActor> NewActorClass, FGameplayTag SocketTag, FName SocketName);

protected:
    /* Initialize */

    virtual void FindRootMesh();
    virtual void InitializeSlots();

    /* API */

    virtual bool HasSlot(FGameplayTag InSocketTag) const;
    virtual const FSocketSlot& GetSlot(FGameplayTag InSocketTag);

    virtual bool DoesSocketExist(FName InSocketName) const;

    virtual UStaticMeshComponent* CreateStaticMesh();
    virtual USkeletalMeshComponent* CreateSkeletalMesh();
    virtual AActor* SpawnActor(TSubclassOf<AActor> InActorClass);

    virtual void ApplySlotConfig(const FSocketSlotConfig& InSlotConfig);
};
