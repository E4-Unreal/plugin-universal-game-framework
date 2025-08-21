// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/QuickSlotManagerWidgetBase.h"

void UQuickSlotManagerWidgetBase::NativeOnInitialized()
{
    Super::NativeOnInitialized();

    if (APawn* OwningPlayerPawn = GetOwningPlayerPawn())
    {
        QuickSlotManager = OwningPlayerPawn->GetComponentByClass<UQuickSlotManagerComponent>();
    }
}
