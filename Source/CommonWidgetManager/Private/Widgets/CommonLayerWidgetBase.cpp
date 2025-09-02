// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/CommonLayerWidgetBase.h"

UCommonLayerWidgetBase::UCommonLayerWidgetBase(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer)
{
    bIsBackHandler = true;
}

bool UCommonLayerWidgetBase::NativeOnHandleBackAction()
{
    if (Super::NativeOnHandleBackAction())
    {
        DeactivateWidget();
    }

    return false;
}
