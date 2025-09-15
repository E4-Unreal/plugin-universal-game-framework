// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ItemContainerComponent.generated.h"

class UDataInstanceBase;

UCLASS(meta = (BlueprintSpawnableComponent))
class INVENTORYSYSTEM_API UItemContainerComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
    bool bAutoDestroy;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config", Instanced)
    TArray<TObjectPtr<UDataInstanceBase>> ItemInstances;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config", meta = (MustImplement = "ItemActorInterface"))
    TSubclassOf<AActor> ItemActorClass;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
    FVector SpawnOffset;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config", meta = (ClampMin = 0, ClampMax = 90))
    float ImpulseAngle;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config", meta = (ClampMin = 0))
    float ImpulseStrength;

public:
    UItemContainerComponent(const FObjectInitializer& ObjectInitializer);

    /* ActorComponent */

    virtual void BeginPlay() override;

    /* API */

    UFUNCTION(BlueprintPure)
    FORCEINLINE int32 GetItemCount() const { return ItemInstances.Num(); }

    UFUNCTION(BlueprintPure)
    FORCEINLINE TArray<UDataInstanceBase*> GetItems() const { return ItemInstances; }

    UFUNCTION(BlueprintCallable)
    virtual void SetItems(const TArray<UDataInstanceBase*>& NewItemInstances);

    UFUNCTION(BlueprintCallable)
    virtual void Clear();

    UFUNCTION(BlueprintCallable)
    virtual void TransferItemsToInventory(AActor* TargetActor);

    UFUNCTION(BlueprintCallable)
    virtual void SpawnItems();
};
