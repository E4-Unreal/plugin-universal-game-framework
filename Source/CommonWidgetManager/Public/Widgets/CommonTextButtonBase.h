// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonButtonBase.h"
#include "CommonTextButtonBase.generated.h"

class USizeBox;
class UCommonTextBlock;
class UCommonTextStyle;

/**
 *
 */
UCLASS(Abstract)
class COMMONWIDGETMANAGER_API UCommonTextButtonBase : public UCommonButtonBase
{
    GENERATED_BODY()

private:
    UPROPERTY(meta = (BindWidget))
    TObjectPtr<USizeBox> SizeBox;

    UPROPERTY(meta = (BindWidget))
    TObjectPtr<UCommonTextBlock> TextBlock;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName = "Text", Category = "Config|TextBlock")
	FText TextOverride;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName = "Horizontal Alignment", Category = "Config|TextBlock")
	TEnumAsByte<EHorizontalAlignment> HorizontalAlignmentOverride;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName = "Vertical Alignment", Category = "Config|TextBlock")
	TEnumAsByte<EVerticalAlignment> VerticalAlignmentOverride;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName = "Padding", Category = "Config|TextBlock")
	FMargin PaddingOverride;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName = "Width", Category = "Config|SizeBox", meta = (editcondition = "bOverride_Width"))
	float WidthOverride;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName = "Height", Category = "Config|SizeBox", meta = (editcondition = "bOverride_Height"))
	float HeightOverride;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName = "Min Desired Width", Category = "Config|SizeBox", meta = (editcondition = "bOverride_MinDesiredWidth"))
	float MinDesiredWidthOverride;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName = "Min Desired Height", Category = "Config|SizeBox", meta = (editcondition = "bOverride_MinDesiredHeight"))
	float MinDesiredHeightOverride;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName = "Max Desired Width", Category = "Config|SizeBox", meta = (editcondition = "bOverride_MaxDesiredWidth"))
	float MaxDesiredWidthOverride;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName = "Max Desired Height", Category = "Config|SizeBox", meta = (editcondition = "bOverride_MaxDesiredHeight"))
	float MaxDesiredHeightOverride;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName = "Min Aspect Ratio", Category = "Config|SizeBox", meta = (editcondition = "bOverride_MinAspectRatio"))
	float MinAspectRatioOverride;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName = "Max Aspect Ratio", Category = "Config|SizeBox", meta = (editcondition = "bOverride_MaxAspectRatio"))
	float MaxAspectRatioOverride;

	UPROPERTY(EditAnywhere, Category = "Config|SizeBox", meta = (InlineEditConditionToggle))
	uint8 bOverride_Width : 1;

	UPROPERTY(EditAnywhere, Category = "Config|SizeBox", meta = (InlineEditConditionToggle))
	uint8 bOverride_Height : 1;

	UPROPERTY(EditAnywhere, Category = "Config|SizeBox", meta = (InlineEditConditionToggle))
	uint8 bOverride_MinDesiredWidth : 1;

	UPROPERTY(EditAnywhere, Category = "Config|SizeBox", meta = (InlineEditConditionToggle))
	uint8 bOverride_MinDesiredHeight : 1;

	UPROPERTY(EditAnywhere, Category = "Config|SizeBox", meta = (InlineEditConditionToggle))
	uint8 bOverride_MaxDesiredWidth : 1;

	UPROPERTY(EditAnywhere, Category = "Config|SizeBox", meta = (InlineEditConditionToggle))
	uint8 bOverride_MaxDesiredHeight : 1;

	UPROPERTY(EditAnywhere, Category = "Config|SizeBox", meta = (InlineEditConditionToggle))
	uint8 bOverride_MinAspectRatio : 1;

	UPROPERTY(EditAnywhere, Category = "Config|SizeBox", meta = (InlineEditConditionToggle))
	uint8 bOverride_MaxAspectRatio : 1;

public:
    UFUNCTION(BlueprintPure)
    FORCEINLINE USizeBox* GetSizeBox() const { return SizeBox; }

    UFUNCTION(BlueprintPure)
    FORCEINLINE UCommonTextBlock* GetTextBlock() const { return TextBlock; }

public:
    UCommonTextButtonBase(const FObjectInitializer& ObjectInitializer);

    /* API */

    UFUNCTION(BlueprintCallable)
    virtual TSubclassOf<UCommonTextStyle> GetDefaultTextStyleClass() const;

protected:
    /* UserWidget */

    virtual void NativePreConstruct() override;

    /* CommonButtonBase */

    virtual void NativeOnCurrentTextStyleChanged() override;
};
