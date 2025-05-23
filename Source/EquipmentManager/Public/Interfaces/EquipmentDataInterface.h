// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "GameplayTags.h"
#include "EquipmentDataInterface.generated.h"

UINTERFACE(MinimalAPI, Blueprintable, BlueprintType)
class UEquipmentDataInterface : public UInterface
{
    GENERATED_BODY()
};

/**
 * 장비와 관련된 정적 데이터 전용 인터페이스로 DataAsset에서 구현되어야 합니다.
 */
class EQUIPMENTMANAGER_API IEquipmentDataInterface
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
    TSubclassOf<AActor> GetActorClass() const;

    UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
    FGameplayTag GetEquipmentType() const;
};
