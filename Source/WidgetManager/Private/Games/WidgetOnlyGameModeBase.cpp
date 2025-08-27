// Fill out your copyright notice in the Description page of Project Settings.


#include "Games/WidgetOnlyGameModeBase.h"

#include "Components/WidgetManagerComponentBase.h"
#include "FunctionLibraries/WidgetManagerFunctionLibrary.h"

const FName AWidgetOnlyGameModeBase::WidgetManagerName(TEXT("WidgetManager"));

AWidgetOnlyGameModeBase::AWidgetOnlyGameModeBase(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer)
{
    /* WidgetManager */

    WidgetManager = CreateDefaultSubobject<UWidgetManagerComponentBase>(WidgetManagerName);
}

void AWidgetOnlyGameModeBase::BeginPlay()
{
    Super::BeginPlay();

    UWidgetManagerFunctionLibrary::SetPlayerUIMode(GetWorld()->GetFirstPlayerController());
}
