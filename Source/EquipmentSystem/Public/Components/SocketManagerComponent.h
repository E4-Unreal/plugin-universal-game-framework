// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameplayTagContainer.h"
#include "Types/SocketActorSlot.h"
#include "SocketManagerComponent.generated.h"

UCLASS(meta = (BlueprintSpawnableComponent))
class EQUIPMENTSYSTEM_API USocketManagerComponent : public UActorComponent
{
    GENERATED_BODY()

private:
    TWeakObjectPtr<UMeshComponent> TargetMesh;

protected:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
    TMap<FGameplayTag, FName> SocketNameMap;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config", meta = (ShowOnlyInnerProperties, SkipUCSModifiedProperties))
    FBodyInstance OverrideBodyInstance;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, ReplicatedUsing = OnRep_SocketActorSlots, Transient, Category = "State")
    TArray<FSocketActorSlot> SocketActorSlots;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Transient, Category = "State")
    TMap<FGameplayTag, TObjectPtr<AActor>> SocketActorMap;

public:
    USocketManagerComponent();

    virtual void PostInitProperties() override;
    virtual void BeginPlay() override;
    virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

    UFUNCTION(BlueprintCallable)
    virtual void SetTargetMesh(UMeshComponent* InTargetMesh);

    UFUNCTION(BlueprintCallable)
    virtual void AttachActorToSocket(const FGameplayTag& SocketTag, AActor* Actor);

    UFUNCTION(BlueprintCallable)
    virtual void SpawnActorToSocket(const FGameplayTag& SocketTag, TSubclassOf<AActor> ActorClass);

    UFUNCTION(BlueprintCallable)
    virtual void SpawnSkeletalMeshToSocket(const FGameplayTag& SocketTag, USkeletalMesh* SkeletalMesh);

    UFUNCTION(BlueprintCallable)
    virtual void SpawnStaticMeshToSocket(const FGameplayTag& SocketTag, UStaticMesh* StaticMesh);

    UFUNCTION(BlueprintCallable)
    virtual void SpawnMeshToSocket(const FGameplayTag& SocketTag, UStreamableRenderAsset* Mesh);

    /* Query */

    UFUNCTION(BlueprintPure)
    AActor* GetActorByTag(const FGameplayTag& SocketTag) const { return SocketActorMap.FindRef(SocketTag); }

protected:
    virtual void FindTargetMesh();

    virtual void Refresh();

    virtual void RegisterSocketActor(const FGameplayTag& SocketTag, AActor* Actor);

    virtual void UnRegisterSocketActor(const FGameplayTag& SocketTag, AActor* Actor);

    UFUNCTION(BlueprintCallable)
    virtual AActor* SpawnActor(TSubclassOf<AActor> ActorClass);

    template<typename T = AActor>
    T* SpawnActor(TSubclassOf<AActor> ActorClass = T::StaticClass()) { return Cast<T>(SpawnActor(ActorClass)); }

    virtual AActor* SpawnActorDeferred(TSubclassOf<AActor> ActorClass);

    template<typename T = AActor>
    T* SpawnActorDeferred(TSubclassOf<AActor> ActorClass = T::StaticClass()) { return Cast<T>(SpawnActorDeferred(ActorClass)); }

    /* Query */

    FORCEINLINE bool ShouldReplicate() const { return GetOwner()->GetIsReplicated(); }

    UFUNCTION(BlueprintPure)
    bool DoesSocketExist(const FGameplayTag& SocketTag) const;

    UFUNCTION(BlueprintPure)
    FName GetSocketName(const FGameplayTag& SocketTag) const { return SocketNameMap.Contains(SocketTag) ? SocketNameMap[SocketTag] : FName(NAME_None); }

    UFUNCTION(BlueprintPure)
    FORCEINLINE UMeshComponent* GetTargetMesh() const { return TargetMesh.Get(); }

    /* Replicate */

    UFUNCTION()
    virtual void OnRep_SocketActorSlots(const TArray<FSocketActorSlot>& OldSocketActorSlots);
};
