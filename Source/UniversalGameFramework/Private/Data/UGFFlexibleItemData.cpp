// Fill out your copyright notice in the Description page of Project Settings.


#include "Data/UGFFlexibleItemData.h"

#include "Data/UGFItemInstance.h"
#include "Data/ItemDataFragment.h"
#include "Data/ProductDataFragment.h"
#include "Data/WeaponDataFragment.h"

UUGFFlexibleItemData::UUGFFlexibleItemData(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer)
{
    DataObjectClass = UUGFItemInstance::StaticClass();

    auto ItemDataFragment = CreateFragment<UItemDataFragment>();
    Fragments.Emplace(ItemDataFragment);

    auto ProductDataFragment = CreateFragment<UProductDataFragment>();
    Fragments.Emplace(ProductDataFragment);

    auto WeaponDataFragment = CreateFragment<UWeaponDataFragment>();
    Fragments.Emplace(WeaponDataFragment);
}

FPrimaryAssetId UUGFFlexibleItemData::GetPrimaryAssetId() const
{
    return FPrimaryAssetId("Item", FName(FString::FromInt(ID)));
}

int32 UUGFFlexibleItemData::GetMaxStack_Implementation() const
{
    auto ItemDataFragment = GetFragmentByInterface<UItemDataInterface>();

    return ItemDataFragment ? IItemDataInterface::Execute_GetMaxStack(ItemDataFragment) : 0;
}

FGameplayTag UUGFFlexibleItemData::GetItemType_Implementation() const
{
    auto ItemDataFragment = GetFragmentByInterface<UItemDataInterface>();

    return ItemDataFragment ? IItemDataInterface::Execute_GetItemType(ItemDataFragment) : FGameplayTag::EmptyTag;
}

TSoftObjectPtr<UMaterialInterface> UUGFFlexibleItemData::GetMaterial_Implementation() const
{
    auto ItemDataFragment = GetFragmentByInterface<UItemDataInterface>();

    return ItemDataFragment ? IItemDataInterface::Execute_GetMaterial(ItemDataFragment) : nullptr;
}

const FGameplayTag UUGFFlexibleItemData::GetCurrencyType_Implementation() const
{
    auto ProductDataFragment = GetFragmentByInterface<UProductInterface>();

    return ProductDataFragment ? IProductInterface::Execute_GetCurrencyType(ProductDataFragment) : FGameplayTag::EmptyTag;
}

int32 UUGFFlexibleItemData::GetBuyPrice_Implementation() const
{
    auto ProductDataFragment = GetFragmentByInterface<UProductInterface>();

    return ProductDataFragment ? IProductInterface::Execute_GetBuyPrice(ProductDataFragment) : 0;
}

int32 UUGFFlexibleItemData::GetSellPrice_Implementation() const
{
    auto ProductDataFragment = GetFragmentByInterface<UProductInterface>();

    return ProductDataFragment ? IProductInterface::Execute_GetSellPrice(ProductDataFragment) : 0;
}

TSubclassOf<AActor> UUGFFlexibleItemData::GetActorClass_Implementation() const
{
    auto WeaponDataFragment = GetFragmentByInterface<UWeaponDataInterface>();

    return WeaponDataFragment ? IWeaponDataInterface::Execute_GetActorClass(WeaponDataFragment) : nullptr;
}

FGameplayTag UUGFFlexibleItemData::GetSlotType_Implementation() const
{
    auto WeaponDataFragment = GetFragmentByInterface<UWeaponDataInterface>();

    return WeaponDataFragment ? IWeaponDataInterface::Execute_GetSlotType(WeaponDataFragment) : FGameplayTag::EmptyTag;
}

FName UUGFFlexibleItemData::GetActiveSocketName_Implementation() const
{
    auto WeaponDataFragment = GetFragmentByInterface<UWeaponDataInterface>();

    return WeaponDataFragment ? IWeaponDataInterface::Execute_GetActiveSocketName(WeaponDataFragment) : NAME_None;
}

FName UUGFFlexibleItemData::GetInActiveSocketName_Implementation() const
{
    auto WeaponDataFragment = GetFragmentByInterface<UWeaponDataInterface>();

    return WeaponDataFragment ? IWeaponDataInterface::Execute_GetInActiveSocketName(WeaponDataFragment) : NAME_None;
}

float UUGFFlexibleItemData::GetMaxDurability_Implementation() const
{
    auto WeaponDataFragment = GetFragmentByInterface<UWeaponDataInterface>();

    return WeaponDataFragment ? IWeaponDataInterface::Execute_GetMaxDurability(WeaponDataFragment) : 0.0f;
}
