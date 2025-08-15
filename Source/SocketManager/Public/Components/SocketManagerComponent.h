// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameplayTagContainer.h"
#include "Types/SocketActorSlot.h"
#include "SocketManagerComponent.generated.h"

UCLASS(meta = (BlueprintSpawnableComponent))
class SOCKETMANAGER_API USocketManagerComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
    TMap<FGameplayTag, FName> SocketNameMap;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config", meta = (ShowOnlyInnerProperties, SkipUCSModifiedProperties))
    FBodyInstance OverrideBodyInstance;

protected:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Reference", Transient)
    TWeakObjectPtr<UMeshComponent> TargetMesh;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, ReplicatedUsing = OnRep_SocketActorSlots, Transient, Category = "State")
    TArray<FSocketActorSlot> SocketActorSlots;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Transient, Category = "State")
    TMap<FGameplayTag, TObjectPtr<AActor>> SocketActorMap;

public:
    USocketManagerComponent();

    virtual void PostInitProperties() override;
    virtual void InitializeComponent() override;
    virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

    UFUNCTION(BlueprintCallable)
    virtual void SetTargetMesh(UMeshComponent* InTargetMesh);

    UFUNCTION(BlueprintCallable)
    virtual bool AttachActorToSocket(const FGameplayTag& SocketTag, AActor* Actor);

    UFUNCTION(BlueprintCallable)
    virtual AActor* DetachActorFromSocket(const FGameplayTag& SocketTag);

    UFUNCTION(BlueprintCallable)
    virtual bool SpawnActorToSocket(const FGameplayTag& SocketTag, TSubclassOf<AActor> ActorClass);

    UFUNCTION(BlueprintCallable)
    virtual bool SpawnSkeletalMeshToSocket(const FGameplayTag& SocketTag, USkeletalMesh* SkeletalMesh);

    UFUNCTION(BlueprintCallable)
    virtual bool SpawnStaticMeshToSocket(const FGameplayTag& SocketTag, UStaticMesh* StaticMesh);

    UFUNCTION(BlueprintCallable)
    virtual bool SpawnMeshToSocket(const FGameplayTag& SocketTag, UStreamableRenderAsset* Mesh);

    UFUNCTION(BlueprintCallable)
    virtual void SwapSockets(const FGameplayTag& SourceTag, const FGameplayTag& DestinationTag);

    UFUNCTION(BlueprintCallable)
    virtual void ClearSocket(const FGameplayTag& SourceTag);

    /* Query */

    UFUNCTION(BlueprintPure)
    bool IsSocketEmpty(const FGameplayTag& SocketTag) const { return !SocketActorMap.Contains(SocketTag); }

    UFUNCTION(BlueprintPure)
    AActor* GetActorByTag(const FGameplayTag& SocketTag) const { return SocketActorMap.FindRef(SocketTag); }

protected:
    virtual void FindTargetMesh();

    virtual void Refresh();

    virtual void RegisterSocketActor(const FGameplayTag& SocketTag, AActor* Actor);

    virtual void UnRegisterSocketActor(const FGameplayTag& SocketTag);

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
    bool IsSocketValid(const FGameplayTag& SocketTag) const { return SocketNameMap.Contains(SocketTag); }

    UFUNCTION(BlueprintPure)
    bool DoesSocketExist(const FGameplayTag& SocketTag) const { return TargetMesh.IsValid() && TargetMesh->DoesSocketExist(GetSocketName(SocketTag)); }

    UFUNCTION(BlueprintPure)
    FName GetSocketName(const FGameplayTag& SocketTag) const { return SocketNameMap.FindRef(SocketTag); }

    /* Replicate */

    UFUNCTION()
    virtual void OnRep_SocketActorSlots(const TArray<FSocketActorSlot>& OldSocketActorSlots);
};
