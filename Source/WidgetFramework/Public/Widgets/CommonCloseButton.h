// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonTextButton.h"
#include "CommonCloseButton.generated.h"

/**
 *
 */
UCLASS(Abstract)
class WIDGETFRAMEWORK_API UCommonCloseButton : public UCommonTextButton
{
    GENERATED_BODY()

public:
    UCommonCloseButton(const FObjectInitializer& ObjectInitializer);

protected:
    virtual void NativeOnClicked() override;
};
