// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Data/DataDefinitionBase.h"
#include "Interfaces/ItemDataInterface.h"
#include "Interfaces/MeshDataInterface.h"
#include "Interfaces/ProductDataInterface.h"
#include "Interfaces/SlotDataInterface.h"
#include "UGFItemDefinition.generated.h"

/**
 *
 */
UCLASS()
class UNIVERSALGAMEFRAMEWORK_API UUGFItemDefinition : public UDataDefinitionBase,
    public IMeshDataInterface,
    public ISlotDataInterface,
    public IItemDataInterface,
    public IProductDataInterface
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
    TSoftObjectPtr<UTexture2D> ThumbnailTexture;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
    TSoftObjectPtr<UStaticMesh> StaticMesh;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
    TSoftObjectPtr<USkeletalMesh> SkeletalMesh;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
    TSoftObjectPtr<UMaterialInterface> Material;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
    TSoftClassPtr<UAnimInstance> AnimationClass;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config", meta = (ClampMin = 1))
    int32 MaxStack;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config", meta = (Categories = "Item"))
    FGameplayTag ItemType;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config", meta = (Categories = "Currency"))
    FGameplayTag CurrencyType;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
    int32 BuyPrice;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
    int32 SellPrice;

public:
    UUGFItemDefinition();

    /* MeshDataInterface */

    virtual TSoftObjectPtr<UStaticMesh> GetStaticMesh_Implementation() const override { return StaticMesh; }
    virtual TSoftObjectPtr<USkeletalMesh> GetSkeletalMesh_Implementation() const override { return SkeletalMesh; }
    virtual TSoftObjectPtr<UMaterialInterface> GetMaterial_Implementation() const override { return Material; }
    virtual TSoftClassPtr<UAnimInstance> GetAnimationClass_Implementation() const override { return AnimationClass; }

    /* SlotDataInterface */

    virtual TSoftObjectPtr<UTexture2D> GetThumbnailTexture_Implementation() const override { return ThumbnailTexture; }

    /* ItemDataInterface */

    virtual int32 GetMaxStack_Implementation() const override { return MaxStack; }
    virtual FGameplayTag GetItemType_Implementation() const override { return ItemType; }

    /* ProductInterface */

    virtual const FGameplayTag GetCurrencyType_Implementation() const override { return CurrencyType; }
    virtual int32 GetBuyPrice_Implementation() const override { return BuyPrice; }
    virtual int32 GetSellPrice_Implementation() const override { return SellPrice; }
};
