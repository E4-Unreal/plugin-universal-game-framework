// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameplayTagContainer.h"
#include "SocketManagerComponent.generated.h"

class ASkeletalMeshActor;
class AStaticMeshActor;

UCLASS(meta = (BlueprintSpawnableComponent))
class EQUIPMENTSYSTEM_API USocketManagerComponent : public UActorComponent
{
    GENERATED_BODY()

private:
    TWeakObjectPtr<USkeletalMeshComponent> TargetMesh;

protected:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
    TMap<FGameplayTag, FName> SocketNameMap;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config", meta = (ShowOnlyInnerProperties, SkipUCSModifiedProperties))
    FBodyInstance OverrideBodyInstance;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Transient, Category = "State")
    TMap<FGameplayTag, TObjectPtr<AActor>> SocketActorMap;

public:
    USocketManagerComponent();

    virtual void InitializeComponent() override;

    UFUNCTION(BlueprintCallable)
    virtual void SetTargetMesh(USkeletalMeshComponent* Value);

    UFUNCTION(BlueprintCallable)
    virtual void AttachActorToSocket(const FGameplayTag& SocketTag, AActor* Actor);

    UFUNCTION(BlueprintCallable)
    virtual void SpawnActorToSocket(const FGameplayTag& SocketTag, TSubclassOf<AActor> ActorClass);

    UFUNCTION(BlueprintCallable)
    virtual void SpawnSkeletalMeshToSocket(const FGameplayTag& SocketTag, USkeletalMesh* SkeletalMesh, TSubclassOf<ASkeletalMeshActor> SkeletalMeshActorClass = nullptr);

    UFUNCTION(BlueprintCallable)
    virtual void SpawnStaticMeshToSocket(const FGameplayTag& SocketTag, UStaticMesh* StaticMesh, TSubclassOf<AStaticMeshActor> StaticMeshActorClass = nullptr);

protected:
    UFUNCTION(BlueprintCallable)
    virtual AActor* SpawnActor(TSubclassOf<AActor> ActorClass);

    template<typename T = AActor>
    T* SpawnActor(TSubclassOf<AActor> ActorClass) { return Cast<T>(SpawnActor(ActorClass)); }

    virtual AActor* SpawnActorDeferred(TSubclassOf<AActor> ActorClass);

    template<typename T = AActor>
    T* SpawnActorDeferred(TSubclassOf<AActor> ActorClass) { return Cast<T>(SpawnActorDeferred(ActorClass)); }

    UFUNCTION(BlueprintCallable)
    virtual ASkeletalMeshActor* SpawnSkeletalMeshActor(USkeletalMesh* SkeletalMesh, TSubclassOf<ASkeletalMeshActor> SkeletalMeshActorClass = nullptr);

    UFUNCTION(BlueprintCallable)
    virtual AStaticMeshActor* SpawnStaticMeshActor(UStaticMesh* StaticMesh, TSubclassOf<AStaticMeshActor> StaticMeshActorClass = nullptr);

    UFUNCTION(BlueprintCallable)
    virtual void SetBodyInstance(UPrimitiveComponent* PrimitiveComponent);

    UFUNCTION(BlueprintPure)
    bool DoesSocketExist(const FGameplayTag& SocketTag) const;

    UFUNCTION(BlueprintPure)
    FName GetSocketName(const FGameplayTag& SocketTag) const { return SocketNameMap.Contains(SocketTag) ? SocketNameMap[SocketTag] : FName(NAME_None); }

    UFUNCTION(BlueprintPure)
    FORCEINLINE USkeletalMeshComponent* GetTargetMesh() const { return TargetMesh.Get(); }
};
