// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SocketMeshActor.generated.h"

UCLASS()
class EQUIPMENTSYSTEM_API ASocketMeshActor : public AActor
{
    GENERATED_BODY()

protected:
    static const FName DefaultSceneRootName;
    static const FName SkeletalMeshComponentName;
    static const FName StaticMeshComponentName;

private:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component", meta = (AllowPrivateAccess = "true"))
    TObjectPtr<USceneComponent> DefaultSceneRoot;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component", meta = (AllowPrivateAccess = "true"))
    TObjectPtr<USkeletalMeshComponent> SkeletalMeshComponent;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component", meta = (AllowPrivateAccess = "true"))
    TObjectPtr<UStaticMeshComponent> StaticMeshComponent;

public:
    ASocketMeshActor(const FObjectInitializer& ObjectInitializer);

    UFUNCTION(BlueprintCallable)
    virtual void SetSkeletalMesh(USkeletalMesh* SkeletalMesh);

    UFUNCTION(BlueprintCallable)
    virtual void SetStaticMesh(UStaticMesh* StaticMesh);

    UFUNCTION(BlueprintCallable)
    virtual void SetBodyInstance(const FBodyInstance& OverrideBodyInstance);

protected:
    UFUNCTION(NetMulticast, Reliable)
    void NetMulticast_SetBodyInstance(const FBodyInstance& OverrideBodyInstance);

    virtual void InternalSetBodyInstance(const FBodyInstance& OverrideBodyInstance);

public:
    FORCEINLINE USkeletalMeshComponent* GetSkeletalMeshComponent() const { return SkeletalMeshComponent; }
    FORCEINLINE UStaticMeshComponent* GetStaticMeshComponent() const { return StaticMeshComponent; }
};
