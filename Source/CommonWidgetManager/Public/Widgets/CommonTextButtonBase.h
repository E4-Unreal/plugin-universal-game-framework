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
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
    FText Text;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config", meta = (editcondition = "bOverride_WidthOverride"))
	float WidthOverride;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config", meta = (editcondition = "bOverride_HeightOverride"))
	float HeightOverride;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config", meta = (editcondition = "bOverride_MinDesiredWidth"))
	float MinDesiredWidth;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config", meta = (editcondition = "bOverride_MinDesiredHeight"))
	float MinDesiredHeight;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config", meta = (editcondition = "bOverride_MaxDesiredWidth"))
	float MaxDesiredWidth;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config", meta = (editcondition = "bOverride_MaxDesiredHeight"))
	float MaxDesiredHeight;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config", meta = (editcondition = "bOverride_MinAspectRatio"))
	float MinAspectRatio;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config", meta = (editcondition = "bOverride_MaxAspectRatio" ))
	float MaxAspectRatio;

	UPROPERTY(EditAnywhere, Category = "Config", meta = (InlineEditConditionToggle))
	uint8 bOverride_WidthOverride : 1;

	UPROPERTY(EditAnywhere, Category = "Config", meta = (InlineEditConditionToggle))
	uint8 bOverride_HeightOverride : 1;

	UPROPERTY(EditAnywhere, Category = "Config", meta = (InlineEditConditionToggle))
	uint8 bOverride_MinDesiredWidth : 1;

	UPROPERTY(EditAnywhere, Category = "Config", meta = (InlineEditConditionToggle))
	uint8 bOverride_MinDesiredHeight : 1;

	UPROPERTY(EditAnywhere, Category = "Config", meta = (InlineEditConditionToggle))
	uint8 bOverride_MaxDesiredWidth : 1;

	UPROPERTY(EditAnywhere, Category = "Config", meta = (InlineEditConditionToggle))
	uint8 bOverride_MaxDesiredHeight : 1;

	UPROPERTY(EditAnywhere, Category = "Config", meta = (InlineEditConditionToggle))
	uint8 bOverride_MinAspectRatio : 1;

	UPROPERTY(EditAnywhere, Category = "Config", meta = (InlineEditConditionToggle))
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
