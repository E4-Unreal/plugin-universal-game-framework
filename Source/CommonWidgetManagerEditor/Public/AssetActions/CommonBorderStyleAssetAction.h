// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonStyleAssetActionBase.h"
#include "CommonBorderStyleAssetAction.generated.h"

/**
 *
 */
UCLASS()
class COMMONWIDGETMANAGEREDITOR_API UCommonBorderStyleAssetAction : public UCommonStyleAssetActionBase
{
    GENERATED_BODY()

protected:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
    FName HalfHeightRadiusName;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
    TMap<FName, FVector4> RadiusMap;

public:
    UCommonBorderStyleAssetAction();

protected:
    virtual void OnGenerateInstance(const FAssetData& SelectedAsset) override;
};
