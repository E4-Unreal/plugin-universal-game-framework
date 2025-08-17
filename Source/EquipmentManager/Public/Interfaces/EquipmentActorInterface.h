// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "EquipmentActorInterface.generated.h"

UINTERFACE(MinimalAPI, Blueprintable, BlueprintType)
class UEquipmentActorInterface : public UInterface
{
    GENERATED_BODY()
};

/**
 * 장비 전용 인터페이스로 Actor에서 구현되어야 합니다.
 */
class EQUIPMENTMANAGER_API IEquipmentActorInterface
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
    void SetEquipmentData(UDataAsset* NewEquipmentData);

    UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
    UDataAsset* GetEquipmentData() const;

    UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
    void Equip(AActor* NewOwner);

    UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
    void UnEquip();
};
