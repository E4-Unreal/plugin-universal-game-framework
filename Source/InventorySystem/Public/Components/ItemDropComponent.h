// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ItemDropComponent.generated.h"

class UDataInstanceBase;
class UItemDropConfig;

UCLASS(meta = (BlueprintSpawnableComponent))
class INVENTORYSYSTEM_API UItemDropComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
    bool bAutoDestroy;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
    TObjectPtr<UItemDropConfig> DropConfig;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config", Instanced)
    TObjectPtr<UItemDropConfig> DropConfigInstance;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config", meta = (MustImplement = "ItemActorInterface"))
    TSubclassOf<AActor> ItemActorClass;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
    FVector SpawnOffset;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config", meta = (ClampMin = 0, ClampMax = 90))
    float ImpulseAngle;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config", meta = (ClampMin = 0))
    float ImpulseStrength;

public:
    UItemDropComponent(const FObjectInitializer& ObjectInitializer);

    /* API */

    UFUNCTION(BlueprintCallable)
    virtual bool AddItemsToInventory(AActor* TargetActor);

    UFUNCTION(BlueprintCallable)
    virtual bool DropItems();

protected:
    /* API */

    virtual UItemDropConfig* GetDropConfig() const;
    virtual TArray<UDataInstanceBase*> GetItems() const;
    virtual TSubclassOf<AActor> GetItemActorClass() const;
};
