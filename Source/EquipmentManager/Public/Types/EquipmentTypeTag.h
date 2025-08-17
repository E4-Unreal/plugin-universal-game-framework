// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTags.h"
#include "EquipmentTypeTag.generated.h"

USTRUCT(BlueprintType)
struct EQUIPMENTMANAGER_API FEquipmentTypeTag
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (Categories = "Equipment"))
    FGameplayTag Tag;

    bool IsValid() const { return Tag.IsValid(); }

    bool operator==(const FEquipmentTypeTag& Other) const { return Tag == Other.Tag; }
    bool operator!=(const FEquipmentTypeTag& Other) const { return !(*this == Other); }

    friend uint32 GetTypeHash(const FEquipmentTypeTag& EquipmentType) { return FCrc::MemCrc32(&EquipmentType, sizeof(FEquipmentTypeTag)); }
};
