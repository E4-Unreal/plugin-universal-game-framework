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

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
    float HoveredValueOffset;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
    float PressedValueOffset;

public:
    UCommonButtonStyleAssetAction();

    UFUNCTION(CallInEditor)
    void CopyBrushToHoveredAndPressed();

    // Base TintColor를 기준으로 Hovered, Pressed 시의 TintColor 명도를 조정합니다.
    UFUNCTION(CallInEditor)
    void UpdateValueForHoveredAndPressed();

protected:
    virtual void OnGenerateInstance(const FAssetData& SelectedAsset) override;
};
