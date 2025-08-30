// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonTextButtonBase.h"
#include "CommonTextActionButtonBase.generated.h"

class UBorder;

/**
 *
 */
UCLASS(Abstract)
class COMMONWIDGETMANAGER_API UCommonTextActionButtonBase : public UCommonTextButtonBase
{
    GENERATED_BODY()

private:
    UPROPERTY(meta = (BindWidget))
    TObjectPtr<UBorder> ActionBorder;

    UPROPERTY(meta = (BindWidget))
    TObjectPtr<UCommonTextBlock> ActionTextBlock;

protected:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
    TSubclassOf<UCommonButtonStyle> ActionButtonStyle;

public:
    UFUNCTION(BlueprintPure)
    FORCEINLINE UBorder* GetActionBorder() const { return ActionBorder; }

    UFUNCTION(BlueprintPure)
    FORCEINLINE UCommonTextBlock* GetActionTextBlock() const { return ActionTextBlock; }

protected:
    /* UserWidget */

    virtual void NativePreConstruct() override;

    /* CommonButtonBase */

    virtual void NativeOnHovered() override;
    virtual void NativeOnUnhovered() override;
    virtual void NativeOnPressed() override;
    virtual void NativeOnReleased() override;

    /* API */

    virtual void SetActionButtonNormal();
    virtual void SetActionButtonHovered();
    virtual void SetActionButtonPressed();

    virtual void SetActionBorderBrush(const FSlateBrush& NewBrush);
    virtual void SetActionTextStyle(TSubclassOf<UCommonTextStyle> NewStyle);
};
