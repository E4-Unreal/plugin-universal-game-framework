// Fill out your copyright notice in the Description page of Project Settings.


#include "Objects/WidgetStack.h"

#include "CommonActivatableWidget.h"
#include "Blueprint/UserWidget.h"
#include "Blueprint/WidgetTree.h"
#include "Components/Overlay.h"
#include "Components/OverlaySlot.h"

UWidgetStack::UWidgetStack(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer)
{
    ParentWidget = Cast<UUserWidget>(GetOuter());
    if (ParentWidget.IsValid())
    {
        if (auto RootOverlay = Cast<UOverlay>(ParentWidget->WidgetTree->RootWidget))
        {
            Overlay = CreateDefaultSubobject<UOverlay>(TEXT("Overlay"));
            UOverlaySlot* RootOverlaySlot = RootOverlay->AddChildToOverlay(Overlay);
            RootOverlaySlot->SetVerticalAlignment(VAlign_Fill);
            RootOverlaySlot->SetHorizontalAlignment(HAlign_Fill);
        }
    }
}

UUserWidget* UWidgetStack::ShowWidget(TSubclassOf<UUserWidget> WidgetClass)
{
    UUserWidget* Widget = nullptr;

    if (ParentWidget.IsValid() && Overlay && WidgetClass)
    {
        int32 Index = Widgets.IndexOfByPredicate([WidgetClass](UUserWidget* Widget)
        {
           return Widget->IsA(WidgetClass);
        });

        if (Widgets.IsValidIndex(Index))
        {
            Widget = Widgets[Index];

            if (Index < Widgets.Num() - 1)
            {
                Widgets.RemoveAt(Index);
                Widgets.Emplace(Widget);
            }

            if (UCommonActivatableWidget* CommonActivatableWidget = Cast<UCommonActivatableWidget>(Widget))
            {
                if (!CommonActivatableWidget->IsActivated())
                {
                    CommonActivatableWidget->ActivateWidget();
                }
            }
            else
            {
                if (!Widget->IsVisible())
                {
                    Widget->SetVisibility(ESlateVisibility::Visible);
                }
            }
        }
        else
        {
            Widget = ParentWidget->WidgetTree->ConstructWidget<UUserWidget>(WidgetClass);

            UOverlaySlot* OverlaySlot = Overlay->AddChildToOverlay(Widget);
            OverlaySlot->SetVerticalAlignment(VAlign_Fill);
            OverlaySlot->SetHorizontalAlignment(HAlign_Fill);

            Widgets.Emplace(Widget);

            if (UCommonActivatableWidget* CommonActivatableWidget = Cast<UCommonActivatableWidget>(Widget))
            {
                if (!CommonActivatableWidget->IsActivated())
                {
                    CommonActivatableWidget->ActivateWidget();
                }
            }
            else
            {
                if (!Widget->IsVisible())
                {
                    Widget->SetVisibility(ESlateVisibility::Visible);
                }
            }
        }
    }

    return Widget;
}

bool UWidgetStack::HideWidget(TSubclassOf<UUserWidget> WidgetClass)
{
    bool bHidden = false;

    if (ParentWidget.IsValid() && Overlay && WidgetClass)
    {
        int32 Index = Widgets.IndexOfByPredicate([WidgetClass](UUserWidget* Widget)
        {
           return Widget->IsA(WidgetClass);
        });

        if (Widgets.IsValidIndex(Index))
        {
            UUserWidget* Widget = Widgets[Index];

            if (UCommonActivatableWidget* CommonActivatableWidget = Cast<UCommonActivatableWidget>(Widget))
            {
                if (CommonActivatableWidget->IsActivated())
                {
                    CommonActivatableWidget->DeactivateWidget();
                    bHidden = true;
                }
            }
            else
            {
                if (Widget->IsVisible())
                {
                    Widget->SetVisibility(ESlateVisibility::Collapsed);
                    bHidden = true;
                }
            }
        }
    }

    return bHidden;
}

void UWidgetStack::ToggleWidget(TSubclassOf<UUserWidget> WidgetClass)
{
    if (WidgetClass && !HideWidget(WidgetClass))
    {
        ShowWidget(WidgetClass);
    }
}
