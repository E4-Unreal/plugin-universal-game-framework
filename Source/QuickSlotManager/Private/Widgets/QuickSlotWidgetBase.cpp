// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/QuickSlotWidgetBase.h"

void UQuickSlotWidgetBase::NativeOnInitialized()
{
    Super::NativeOnInitialized();

    if (APawn* OwningPlayerPawn = GetOwningPlayerPawn())
    {
        QuickSlotManager = OwningPlayerPawn->GetComponentByClass<UQuickSlotManagerComponent>();
    }
}
