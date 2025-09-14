// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ItemComponent.generated.h"

class UDataInstanceBase;

UCLASS(meta = (BlueprintSpawnableComponent))
class INVENTORYSYSTEM_API UItemComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config", Instanced)
    TArray<TObjectPtr<UDataInstanceBase>> ItemInstances;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
    TSoftObjectPtr<UStaticMesh> DefaultStaticMesh;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
    bool bAutoDestroy;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
    FText ItemNameFormat;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config|Spawn", meta = (MustImplement = "ItemActorInterface"))
    TSubclassOf<AActor> ItemActorClass;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config|Spawn")
    FVector SpawnOffset;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config|Spawn", meta = (ClampMin = 0, ClampMax = 90))
    float ImpulseAngle;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config|Spawn", meta = (ClampMin = 0))
    float ImpulseStrength;

protected:
    UPROPERTY(VisibleAnywhere, Category = "Reference", Transient)
    TWeakObjectPtr<UStaticMeshComponent> DisplayMesh;

public:
    UItemComponent(const FObjectInitializer& ObjectInitializer);

    /* Object */

#if WITH_EDITOR
    virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
#endif

    /* ActorComponent */

    virtual void InitializeComponent() override;
    virtual void BeginPlay() override;

    /* API */

    UFUNCTION(BlueprintPure)
    FORCEINLINE int32 GetItemCount() const { return ItemInstances.Num(); }

    UFUNCTION(BlueprintPure)
    virtual FText GetItemName() const;

    UFUNCTION(BlueprintPure)
    FORCEINLINE TArray<UDataInstanceBase*> GetItems() const { return ItemInstances; }

    UFUNCTION(BlueprintPure)
    virtual UStaticMesh* GetStaticMesh() const;

    UFUNCTION(BlueprintCallable)
    virtual void SetDisplayMesh(UStaticMeshComponent* NewDisplayMesh);

    UFUNCTION(BlueprintCallable)
    virtual void SetItems(const TArray<UDataInstanceBase*>& NewItemInstances);

    UFUNCTION(BlueprintCallable)
    virtual void Refresh();

    UFUNCTION(BlueprintCallable)
    virtual void Clear();

    UFUNCTION(BlueprintCallable)
    virtual void TransferItemsToInventory(AActor* TargetActor);

    UFUNCTION(BlueprintCallable)
    virtual void SpawnItems();

protected:
    /* API */

    virtual void FindDisplayMesh();
};
