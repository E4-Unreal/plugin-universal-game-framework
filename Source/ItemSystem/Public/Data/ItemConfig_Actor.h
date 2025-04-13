// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ItemConfig.h"
#include "ItemConfig_Actor.generated.h"

USTRUCT(Atomic, BlueprintType)
struct FItemConfigData_Actor : public FTableRowBase
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TSoftObjectPtr<UStaticMesh> StaticMesh;

    static const FItemConfigData_Actor EmptyData;

    FORCEINLINE bool operator ==(const FItemConfigData_Actor& Other) const
    {
        return StaticMesh == Other.StaticMesh;
    }

    FORCEINLINE bool operator !=(const FItemConfigData_Actor& Other) const
    {
        return !(*this == Other);
    }
};

/**
 * ItemActorBase 전용 ItemConfig
 */
UCLASS()
class ITEMSYSTEM_API UItemConfig_Actor : public UItemConfig
{
    GENERATED_BODY()

protected:
    UPROPERTY(EditDefaultsOnly, BlueprintGetter = GetData, Category = "Config")
    FItemConfigData_Actor Data;

public:
    UFUNCTION(BlueprintGetter)
    const FORCEINLINE FItemConfigData_Actor& GetData() const { return Data; }

protected:
    virtual void OnUpdate(FTableRowBase* TableRow) override;
    virtual void OnReset() override;
};
