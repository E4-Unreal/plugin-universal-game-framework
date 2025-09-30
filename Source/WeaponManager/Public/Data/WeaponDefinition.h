// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Data/DataDefinitionBase.h"
#include "Interfaces/SlotDataInterface.h"
#include "Interfaces/WeaponDataInterface.h"
#include "WeaponDefinition.generated.h"

/**
 *
 */
UCLASS()
class WEAPONMANAGER_API UWeaponDefinition : public UDataDefinitionBase,
    public ISlotDataInterface,
    public IWeaponDataInterface
{
    GENERATED_BODY()

protected:
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TSoftObjectPtr<UTexture2D> ThumbnailTexture;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TSoftObjectPtr<UStaticMesh> StaticMesh;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TSoftObjectPtr<USkeletalMesh> SkeletalMesh;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (MustImplement = "WeaponActorInterface"))
    TSubclassOf<AActor> ActorClass;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FGameplayTag SlotType;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FName ActiveSocketName;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FName InActiveSocketName;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float MaxDurability;

public:
    UWeaponDefinition();

    /* SlotDataInterface */

    virtual TSoftObjectPtr<UTexture2D> GetThumbnailTexture_Implementation() const override { return ThumbnailTexture; }

    /* WeaponDataInterface */

    virtual FName GetActiveSocketName_Implementation() const override { return ActiveSocketName; }
    virtual TSubclassOf<AActor> GetActorClass_Implementation() const override { return ActorClass; }
    virtual FName GetInActiveSocketName_Implementation() const override { return InActiveSocketName; }
    virtual float GetMaxDurability_Implementation() const override { return MaxDurability; }
    virtual FGameplayTag GetSlotType_Implementation() const override { return SlotType; }
};
