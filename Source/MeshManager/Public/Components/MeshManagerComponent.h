// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "MeshManagerComponent.generated.h"


class IMeshDataInterface;

UCLASS(meta = (BlueprintSpawnableComponent))
class MESHMANAGER_API UMeshManagerComponent : public UActorComponent
{
    GENERATED_BODY()

protected:
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Reference", Transient)
    TWeakObjectPtr<UStaticMeshComponent> StaticMeshComponent;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Reference", Transient)
    TWeakObjectPtr<USkeletalMeshComponent> SkeletalMeshComponent;

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
    TScriptInterface<IMeshDataInterface> MeshData;

public:
    UMeshManagerComponent();

    /* UObject */

#if WITH_EDITOR
    virtual void PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent) override;
#endif

    /* ActorComponent */

    virtual void InitializeComponent() override;

    /* API */

    UFUNCTION(BlueprintCallable, Category = "Reference")
    virtual void SetStaticMeshComponent(UStaticMeshComponent* NewStaticMeshComponent);

    UFUNCTION(BlueprintCallable, Category = "Reference")
    virtual void SetSkeletalMeshComponent(USkeletalMeshComponent* NewSkeletalMeshComponent);

    UFUNCTION(BlueprintCallable)
    virtual void SetMeshData(UDataAsset* NewMeshData);

protected:
    /* Reference */

    virtual void FindStaticMeshComponent();
    virtual void FindSkeletalMeshComponent();

    /* Getter */

    UObject* GetMeshData() const;

    /* API */

    virtual void Refresh();
    virtual void Clear();
    virtual void SetStaticMesh();
    virtual void ClearStaticMesh();
    virtual void SetSkeletalMesh();
    virtual void ClearSkeletalMesh();
};
