// Fill out your copyright notice in the Description page of Project Settings.


#include "Objects/LayerStack.h"

#include "CommonActivatableWidget.h"
#include "Components/Overlay.h"
#include "Components/OverlaySlot.h"
#include "Widgets/CommonActivatableWidgetContainer.h"
#include "Widgets/CustomActivatableWidgetStack.h"

void ULayerStack::InitializeAsStack(UUserWidget* NewParentWidget, UCommonActivatableWidgetStack* NewStack)
{
    ParentWidget = NewParentWidget;
    Stack = NewStack;
    Overlay = nullptr;
    OverlayStack.Empty();
}

void ULayerStack::InitializeAsOverlayStack(UUserWidget* NewParentWidget, UOverlay* NewOverlay, const FTransitionConfig& NewTransitionConfig)
{
    ParentWidget = NewParentWidget;
    Stack = nullptr;
    Overlay = NewOverlay;
    OverlayStack.Empty();
    TransitionConfig = NewTransitionConfig;
}

UCommonActivatableWidget* ULayerStack::ShowWidget(TSubclassOf<UCommonActivatableWidget> WidgetClass)
{
    return IsOverlay() ? AddWidgetToOverlayStack(WidgetClass) : AddWidgetToStack(WidgetClass);
}

bool ULayerStack::HideWidget(TSubclassOf<UCommonActivatableWidget> WidgetClass)
{
    return IsOverlay() ? HideWidgetFromOverlayStack(WidgetClass) : HideWidgetFromStack(WidgetClass);
}

void ULayerStack::ToggleWidget(TSubclassOf<UCommonActivatableWidget> WidgetClass)
{
    if (WidgetClass && !HideWidget(WidgetClass))
    {
        ShowWidget(WidgetClass);
    }
}

UCommonActivatableWidget* ULayerStack::AddWidgetToStack(TSubclassOf<UCommonActivatableWidget> WidgetClass)
{
    UCommonActivatableWidget* Widget = nullptr;

    if (WidgetClass && Stack)
    {
        UCommonActivatableWidget* ActiveWidget = Stack->GetActiveWidget();
        if (ActiveWidget && ActiveWidget->IsA(WidgetClass))
        {
            Widget = ActiveWidget;
        }
        else
        {
            const TArray<UCommonActivatableWidget*>& ExistingWidgets = Stack->GetWidgetList();
            for (UCommonActivatableWidget* ExistingWidget : ExistingWidgets)
            {
                if (ExistingWidget->IsA(WidgetClass))
                {
                    Stack->RemoveWidget(*ExistingWidget);
                    break;
                }
            }
        }

        Widget = Stack->AddWidget(WidgetClass);
    }

    return Widget;
}

UCommonActivatableWidget* ULayerStack::AddWidgetToOverlayStack(TSubclassOf<UCommonActivatableWidget> WidgetClass)
{
    UCommonActivatableWidget* Widget = nullptr;

    if (WidgetClass)
    {
        // 레이어 정렬
        SortOverlayStack();

        // 기존 레이어에 위젯 추가
        for (TObjectPtr<UCommonActivatableWidgetStack> StackInstance : OverlayStack)
        {
            if (UCommonActivatableWidget* ActiveWidget = StackInstance->GetActiveWidget())
            {
                if (ActiveWidget->IsA(WidgetClass))
                {
                    Widget = ActiveWidget;
                    break;
                }
            }
            else
            {
                Widget = StackInstance->AddWidget(WidgetClass);
                break;
            }
        }

        // 새로운 레이어 생성 후 위젯 추가
        if (Widget == nullptr)
        {
            if (UCommonActivatableWidgetStack* StackInstance = AddStackInstance())
            {
                Widget = StackInstance->AddWidget(WidgetClass);
            }
        }
    }

    return Widget;
}

void ULayerStack::SortOverlayStack()
{
    OverlayStack.Sort([](const TObjectPtr<UCommonActivatableWidgetStack>& Left, const TObjectPtr<UCommonActivatableWidgetStack>& Right)
    {
        return Left->GetActiveWidget() || !Right->GetActiveWidget();
    });
}

UCommonActivatableWidgetStack* ULayerStack::AddStackInstance()
{
    if (ParentWidget.IsValid() && Overlay)
    {
        if (UCustomActivatableWidgetStack* StackInstance = ParentWidget->WidgetTree->ConstructWidget<UCustomActivatableWidgetStack>())
        {
            StackInstance->SetTransitionConfig(TransitionConfig);
            if (UOverlaySlot* OverlaySlot = Overlay->AddChildToOverlay(StackInstance))
            {
                OverlaySlot->SetVerticalAlignment(VAlign_Fill);
                OverlaySlot->SetHorizontalAlignment(HAlign_Fill);
                OverlayStack.Emplace(StackInstance);

                return StackInstance;
            }
        }
    }

    return nullptr;
}

bool ULayerStack::HideWidgetFromStack(TSubclassOf<UCommonActivatableWidget> WidgetClass)
{
    if (WidgetClass)
    {
        UCommonActivatableWidget* ActiveWidget = Stack->GetActiveWidget();
        if (ActiveWidget && ActiveWidget->IsA(WidgetClass))
        {
            ActiveWidget->DeactivateWidget();
            return true;
        }
    }

    return false;
}

bool ULayerStack::HideWidgetFromOverlayStack(TSubclassOf<UCommonActivatableWidget> WidgetClass)
{
    if (WidgetClass)
    {
        for (TObjectPtr<UCommonActivatableWidgetStack> StackInstance : OverlayStack)
        {
            UCommonActivatableWidget* ActiveWidget = StackInstance->GetActiveWidget();
            if (ActiveWidget && ActiveWidget->IsA(WidgetClass))
            {
                ActiveWidget->DeactivateWidget();
                return true;
            }
        }
    }

    return false;
}
