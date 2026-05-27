// Fill out your copyright notice in the Description page of Project Settings.


#include "Players/UGFTopViewPlayerController.h"

AUGFTopViewPlayerController::AUGFTopViewPlayerController(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer)
{
    /* PlayerController */

    bEnableMouseOverEvents = true;
    bEnableClickEvents = true;
}
