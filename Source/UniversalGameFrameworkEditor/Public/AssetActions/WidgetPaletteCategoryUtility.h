// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AssetActionUtility.h"
#include "WidgetPaletteCategoryUtility.generated.h"

/**
 *
 */
UCLASS()
class UNIVERSALGAMEFRAMEWORKEDITOR_API UWidgetPaletteCategoryUtility : public UAssetActionUtility
{
    GENERATED_BODY()

public:
    UWidgetPaletteCategoryUtility();

	UFUNCTION(CallInEditor)
	void SetPaletteCategory(FString NewCategory);

protected:
    static UUserWidget* GetUserWidget(const FAssetData& AssetData);
};
