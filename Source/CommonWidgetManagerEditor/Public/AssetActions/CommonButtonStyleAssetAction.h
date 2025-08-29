// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonStyleAssetActionBase.h"
#include "CommonButtonStyleAssetAction.generated.h"

/**
 *
 */
UCLASS()
class COMMONWIDGETMANAGEREDITOR_API UCommonButtonStyleAssetAction : public UCommonStyleAssetActionBase
{
    GENERATED_BODY()

protected:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
    FName HalfHeightRadiusName;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
    TMap<FName, FVector4> RadiusMap;

public:
    UCommonButtonStyleAssetAction();

protected:
    virtual void OnGenerateInstance(const FAssetData& SelectedAsset) override;
};
