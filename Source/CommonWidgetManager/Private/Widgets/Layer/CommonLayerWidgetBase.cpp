// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/Layer/CommonLayerWidgetBase.h"

UCommonLayerWidgetBase::UCommonLayerWidgetBase(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer)
{
    bIsBackHandler = true;
    bIsModal = true;

    UIInputConfig = FUIInputConfig(ECommonInputMode::All, EMouseCaptureMode::NoCapture, EMouseLockMode::DoNotLock);
    UIInputConfig.bIgnoreLookInput = false;
    UIInputConfig.bIgnoreMoveInput = false;
}

TOptional<FUIInputConfig> UCommonLayerWidgetBase::GetDesiredInputConfig() const
{
    if (GetClass()->IsFunctionImplementedInScript(GET_FUNCTION_NAME_CHECKED(ThisClass, BP_GetDesiredInputConfig)))
    {
        return BP_GetDesiredInputConfig();
    }

    return UIInputConfig;
}
