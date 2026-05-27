// Fill out your copyright notice in the Description page of Project Settings.


#include "Players/UGFPlayerController.h"

#include "Components/PlayerWidgetManagerComponent.h"
#include "Widgets/CommonLayoutWidget.h"

const FName AUGFPlayerController::PlayerWidgetManagerName(TEXT("PlayerWidgetManager"));


AUGFPlayerController::AUGFPlayerController(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer)
{
    /* PlayerWidgetManagerComponent */

    PlayerWidgetManager = CreateDefaultSubobject<UPlayerWidgetManagerComponent>(PlayerWidgetManagerName);
    PlayerWidgetManager->LayoutWidgetClass = UCommonLayoutWidget::StaticClass();
}
