// Fill out your copyright notice in the Description page of Project Settings.


#include "Games/WidgetGameModeBase.h"

#include "Components/WidgetManagerComponent.h"

const FName AWidgetGameModeBase::WidgetManagerName(TEXT("WidgetManager"));

AWidgetGameModeBase::AWidgetGameModeBase(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer)
{
    /* GameModeBase */

    DefaultPawnClass = nullptr;
    HUDClass = nullptr;

    /* WidgetManager */

    WidgetManager = CreateDefaultSubobject<UWidgetManagerComponent>(WidgetManagerName);
}
