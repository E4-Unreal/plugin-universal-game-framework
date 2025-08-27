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
    FVector2D Size;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
    FText Text;

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
