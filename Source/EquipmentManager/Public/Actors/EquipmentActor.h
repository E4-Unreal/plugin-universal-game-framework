// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interfaces/EquipmentActorInterface.h"
#include "EquipmentActor.generated.h"

UCLASS()
class EQUIPMENTMANAGER_API AEquipmentActor : public AActor, public IEquipmentActorInterface
{
    GENERATED_BODY()

protected:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config", meta = (MustImplement = "EquipmentDataInterface"))
    TObjectPtr<UDataAsset> EquipmentData;

public:
    AEquipmentActor(const FObjectInitializer& ObjectInitializer);

    /* EquipmentInterface */

    virtual UDataAsset* GetEquipmentData_Implementation() const override { return EquipmentData; }
    virtual void SetEquipmentData_Implementation(UDataAsset* NewEquipmentData) override;
    virtual void Equip_Implementation(AActor* NewOwner) override;
    virtual void UnEquip_Implementation() override;
};
