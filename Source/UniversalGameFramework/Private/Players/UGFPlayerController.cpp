// Fill out your copyright notice in the Description page of Project Settings.


#include "Players/UGFPlayerController.h"

#include "Components/PlayerWidgetManagerComponent.h"

const FName AUGFPlayerController::PlayerWidgetManagerName(TEXT("PlayerWidgetManager"));


AUGFPlayerController::AUGFPlayerController(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer)
{
    /* APlayerController */

    bEnableMouseOverEvents = true;
    bEnableClickEvents = true;

    /* PlayerWidgetManager */

    PlayerWidgetManager = CreateDefaultSubobject<UPlayerWidgetManagerComponent>(PlayerWidgetManagerName);
}
