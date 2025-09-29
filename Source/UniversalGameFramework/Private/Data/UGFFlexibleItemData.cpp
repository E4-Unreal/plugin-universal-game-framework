// Fill out your copyright notice in the Description page of Project Settings.


#include "Data/UGFFlexibleItemData.h"

#include "Data/ItemDataFragment.h"
#include "Data/MeshDataFragment.h"
#include "Data/ProductDataFragment.h"
#include "Data/SlotDataFragment.h"
#include "Data/UGFEquipmentInstance.h"
#include "Data/WeaponDataFragment.h"

UUGFFlexibleItemData::UUGFFlexibleItemData(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer)
{
    // TODO FlexibleItemInstance로 대체
    InstanceDataClass = UUGFEquipmentInstance::StaticClass();

    auto MeshDataFragment = AddFragment<UMeshDataFragment>();
    auto SlotDataFragment = AddFragment<USlotDataFragment>();
    auto ItemDataFragment = AddFragment<UItemDataFragment>();
    auto ProductDataFragment = AddFragment<UProductDataFragment>();
    auto WeaponDataFragment = AddFragment<UWeaponDataFragment>();
}

FPrimaryAssetId UUGFFlexibleItemData::GetPrimaryAssetId() const
{
    return FPrimaryAssetId("Item", FName(FString::FromInt(ID)));
}
