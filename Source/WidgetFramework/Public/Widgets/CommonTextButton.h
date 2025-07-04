// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonButtonBase.h"
#include "CommonTextButton.generated.h"

class UCommonTextBlock;

UCLASS(Abstract)
class WIDGETFRAMEWORK_API UCommonTextButton : public UCommonButtonBase
{
    GENERATED_BODY()

protected:
    UPROPERTY(meta = (BindWidget))
    TObjectPtr<UCommonTextBlock> ButtonTextBlock;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
    FText ButtonText;

public:
    UCommonTextButton(const FObjectInitializer& ObjectInitializer);

protected:
    virtual void NativePreConstruct() override;
    virtual void NativeOnCurrentTextStyleChanged() override;
};
