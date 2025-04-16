// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SocketMeshActor.generated.h"

UCLASS(Abstract)
class EQUIPMENTSYSTEM_API ASocketMeshActor : public AActor
{
    GENERATED_BODY()

protected:
    static const FName MeshComponentName;

private:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component", meta = (AllowPrivateAccess = "true"))
    TObjectPtr<UMeshComponent> MeshComponent;

protected:
    UPROPERTY(ReplicatedUsing = OnRep_Mesh, Transient)
    TObjectPtr<UStreamableRenderAsset> Mesh;

    UPROPERTY(ReplicatedUsing = OnRep_BodyInstance, Transient)
    FBodyInstance BodyInstance;

public:
    ASocketMeshActor(const FObjectInitializer& ObjectInitializer);

    virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

    UFUNCTION(BlueprintCallable)
    virtual void SetMesh(UStreamableRenderAsset* NewMesh);

    UFUNCTION(BlueprintCallable)
    virtual void SetBodyInstance(const FBodyInstance& NewBodyInstance);

protected:
    void ApplyBodyInstance() const;

    UFUNCTION()
    virtual void OnRep_Mesh(UStreamableRenderAsset* OldMesh);

    UFUNCTION()
    virtual void OnRep_BodyInstance();

public:
    FORCEINLINE UMeshComponent* GetMeshComponent() const { return MeshComponent; }

    template<typename T = UMeshComponent>
    T* GetMeshComponent() const { return Cast<T>(MeshComponent); }
};
