// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonStyleAssetActionBase.h"
#include "CommonTextStyleAssetAction.generated.h"

/**
 *
 */
UCLASS()
class COMMONWIDGETMANAGEREDITOR_API UCommonTextStyleAssetAction : public UCommonStyleAssetActionBase
{
    GENERATED_BODY()

protected:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
    TMap<FName, float> FontSizeMap;

public:
    UCommonTextStyleAssetAction();

protected:
    virtual void OnGenerateInstance(const FAssetData& SelectedAsset) override;
};
