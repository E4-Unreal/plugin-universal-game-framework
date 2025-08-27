// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/Common/CommonLayoutWidgetBase.h"

#include "Widgets/CommonActivatableWidgetContainer.h"


UCommonLayoutWidgetBase::UCommonLayoutWidgetBase(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer)
{
    bAutoActivate = true;
}

UCommonActivatableWidget* UCommonLayoutWidgetBase::AddWidget(FGameplayTag LayerTag, TSubclassOf<UCommonActivatableWidget> WidgetClass)
{
    UCommonActivatableWidget* Widget = nullptr;

    if (UCommonActivatableWidgetStack* Layer = GetLayer(LayerTag))
    {
        if (WidgetClass)
        {
            Widget = Layer->AddWidget(WidgetClass);
        }
    }

    return Widget;
}

void UCommonLayoutWidgetBase::RemoveWidget(FGameplayTag LayerTag, UCommonActivatableWidget* Widget)
{
    if (UCommonActivatableWidgetStack* Layer = GetLayer(LayerTag))
    {
        if (Widget)
        {
            Layer->RemoveWidget(*Widget);
        }
    }
}

void UCommonLayoutWidgetBase::SetLayer(FGameplayTag LayerTag, UCommonActivatableWidgetStack* LayerWidget)
{
    if (LayerWidget)
    {
        LayerMap.Emplace(LayerTag, LayerWidget);
    }
}
