// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DynamicData/Public/Data/DefinitionBase.h"
#include "Interfaces/ItemDataInterface.h"
#include "Interfaces/ProductInterface.h"
#include "GameplayTags/CurrencyGameplayTags.h"
#include "UGFItemDefinition.generated.h"

/**
 *
 */
UCLASS()
class UNIVERSALGAMEFRAMEWORK_API UUGFItemDefinition : public UDefinitionBase,
    public IItemDataInterface,
    public IProductInterface
{
    GENERATED_BODY()

protected:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ClampMin = 1))
    int32 MaxStack = 1;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FGameplayTag ItemType;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TSoftObjectPtr<UStaticMesh> StaticMesh;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TSoftObjectPtr<USkeletalMesh> SkeletalMesh;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FText DisplayNameText;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TSoftObjectPtr<UTexture2D> ThumbnailTexture;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Config", meta = (Categories = "Currency"))
    FGameplayTag CurrencyType = Currency::Default;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Config")
    int32 BuyPrice;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Config")
    int32 SellPrice;

public:
    /* ItemDataInterface */

    virtual int32 GetMaxStack_Implementation() const override { return MaxStack; }
    virtual FGameplayTag GetItemType_Implementation() const override { return ItemType; }
    virtual TSoftObjectPtr<UStaticMesh> GetStaticMesh_Implementation() const override { return StaticMesh; }
    virtual TSoftObjectPtr<USkeletalMesh> GetSkeletalMesh_Implementation() const override { return SkeletalMesh; }
    virtual FText GetDisplayNameText_Implementation() const override { return DisplayNameText; }
    virtual TSoftObjectPtr<UTexture2D> GetThumbnailTexture_Implementation() const override { return ThumbnailTexture; }

    /* ProductInterface */

    virtual const FGameplayTag GetCurrencyType_Implementation() const override { return CurrencyType; }
    virtual int32 GetBuyPrice_Implementation() const override { return BuyPrice; }
    virtual int32 GetSellPrice_Implementation() const override { return SellPrice; }
};
