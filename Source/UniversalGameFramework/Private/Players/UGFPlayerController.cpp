// Fill out your copyright notice in the Description page of Project Settings.


#include "Players/UGFPlayerController.h"

#include "Components/CommonWidgetManagerComponent.h"

const FName AUGFPlayerController::WidgetManagerName(TEXT("WidgetManager"));


AUGFPlayerController::AUGFPlayerController(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer)
{
    /* WidgetManager */

    WidgetManager = CreateDefaultSubobject<UCommonWidgetManagerComponent>(WidgetManagerName);
}
