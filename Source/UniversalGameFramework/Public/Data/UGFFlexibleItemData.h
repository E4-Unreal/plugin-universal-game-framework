// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Data/Flexible/FlexibleData.h"
#include "Interfaces/ItemDataInterface.h"
#include "Interfaces/ProductInterface.h"
#include "Interfaces/SlotDataInterface.h"
#include "Interfaces/WeaponDataInterface.h"
#include "UGFFlexibleItemData.generated.h"

class UItemDataFragment;

/**
 *
 */
UCLASS()
class UNIVERSALGAMEFRAMEWORK_API UUGFFlexibleItemData : public UFlexibleData,
    public ISlotDataInterface,
    public IItemDataInterface,
    public IProductInterface,
    public IWeaponDataInterface
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
    TSoftObjectPtr<UTexture2D> ThumbnailTexture;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
    TSoftObjectPtr<UStaticMesh> StaticMesh;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
    TSoftObjectPtr<USkeletalMesh> SkeletalMesh;

public:
    UUGFFlexibleItemData(const FObjectInitializer& ObjectInitializer);

    /* PrimaryDataAsset */

    virtual FPrimaryAssetId GetPrimaryAssetId() const override;

    /* SlotDataInterface */

    virtual TSoftObjectPtr<UTexture2D> GetThumbnailTexture_Implementation() const override { return ThumbnailTexture; }

    /* ItemDataInterface */

    virtual int32 GetMaxStack_Implementation() const override;
    virtual FGameplayTag GetItemType_Implementation() const override;
    virtual TSoftObjectPtr<UStaticMesh> GetStaticMesh_Implementation() const override { return StaticMesh; }
    virtual TSoftObjectPtr<USkeletalMesh> GetSkeletalMesh_Implementation() const override { return SkeletalMesh; }

    /* ProductInterface */

    virtual FText GetDisplayNameText_Implementation() const override { return DisplayName; }
    virtual const FGameplayTag GetCurrencyType_Implementation() const override;
    virtual int32 GetBuyPrice_Implementation() const override;
    virtual int32 GetSellPrice_Implementation() const override;

    /* WeaponDataInterface */

    virtual TSubclassOf<AActor> GetActorClass_Implementation() const override;
    virtual FGameplayTag GetSlotType_Implementation() const override;
    virtual FName GetActiveSocketName_Implementation() const override;
    virtual FName GetInActiveSocketName_Implementation() const override;
    virtual float GetMaxDurability_Implementation() const override;
};
