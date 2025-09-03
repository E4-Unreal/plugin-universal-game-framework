// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/CommonLayoutWidgetBase.h"

#include "Components/Overlay.h"
#include "Components/OverlaySlot.h"
#include "Objects/LayerStack.h"
#include "Widgets/CommonActivatableWidgetContainer.h"
#include "Widgets/Layer/CommonLayerWidgetBase.h"


UCommonLayoutWidgetBase::UCommonLayoutWidgetBase(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer)
{
    bAutoActivate = true;
    bIsBackHandler = true;

    UIInputConfig = FUIInputConfig(ECommonInputMode::All, EMouseCaptureMode::NoCapture, EMouseLockMode::DoNotLock);
    UIInputConfig.bIgnoreLookInput = false;
    UIInputConfig.bIgnoreMoveInput = false;
}

void UCommonLayoutWidgetBase::NativeOnInitialized()
{
    Super::NativeOnInitialized();

    CreateLayerMap();
}

void UCommonLayoutWidgetBase::NativePreConstruct()
{
    Super::NativePreConstruct();

    if (IsDesignTime())
    {
        CreateLayerMap();
    }
}

bool UCommonLayoutWidgetBase::NativeOnHandleBackAction()
{
    if (bIsBackHandler)
    {
        if (!BP_OnHandleBackAction())
        {
            if (EscapeMenuWidgetClass)
            {
                ToggleLayerWidget(EscapeMenuWidgetClass);
            }
        }

        return true;
    }

    return false;
}

TOptional<FUIInputConfig> UCommonLayoutWidgetBase::GetDesiredInputConfig() const
{
    if (GetClass()->IsFunctionImplementedInScript(GET_FUNCTION_NAME_CHECKED(ThisClass, BP_GetDesiredInputConfig)))
    {
        return BP_GetDesiredInputConfig();
    }

    return UIInputConfig;
}

UCommonActivatableWidget* UCommonLayoutWidgetBase::ShowWidget(FGameplayTag LayerTag, TSubclassOf<UCommonActivatableWidget> WidgetClass)
{
    UCommonActivatableWidget* Widget = nullptr;

    if (ULayerStack* Layer = GetLayer(LayerTag))
    {
        Widget = Layer->ShowWidget(WidgetClass);
    }

    return Widget;
}

UCommonActivatableWidget* UCommonLayoutWidgetBase::ShowLayerWidget(TSubclassOf<UCommonLayerWidgetBase> WidgetClass)
{
    UCommonLayerWidgetBase* LayerWidget = WidgetClass->GetDefaultObject<UCommonLayerWidgetBase>();
    return ShowWidget(LayerWidget->GetLayerTag(), WidgetClass);
}

bool UCommonLayoutWidgetBase::HideWidget(FGameplayTag LayerTag, TSubclassOf<UCommonActivatableWidget> WidgetClass)
{
    bool bResult = false;

    if (ULayerStack* Layer = GetLayer(LayerTag))
    {
        bResult = Layer->HideWidget(WidgetClass);
    }

    return bResult;
}

bool UCommonLayoutWidgetBase::HideLayerWidget(TSubclassOf<UCommonLayerWidgetBase> WidgetClass)
{
    UCommonLayerWidgetBase* LayerWidget = WidgetClass->GetDefaultObject<UCommonLayerWidgetBase>();
    return HideWidget(LayerWidget->GetLayerTag(), WidgetClass);
}

void UCommonLayoutWidgetBase::ToggleWidget(FGameplayTag LayerTag, TSubclassOf<UCommonActivatableWidget> WidgetClass)
{
    if (ULayerStack* Layer = GetLayer(LayerTag))
    {
        Layer->ToggleWidget(WidgetClass);
    }
}

void UCommonLayoutWidgetBase::ToggleLayerWidget(TSubclassOf<UCommonLayerWidgetBase> WidgetClass)
{
    UCommonLayerWidgetBase* LayerWidget = WidgetClass->GetDefaultObject<UCommonLayerWidgetBase>();
    ToggleWidget(LayerWidget->GetLayerTag(), WidgetClass);
}

void UCommonLayoutWidgetBase::CreateLayerMap()
{
    if (!LayerMap.IsEmpty()) return;

    for (const auto& [LayerTag, IsOverlay] : LayerConfig)
    {
        ULayerStack* LayerStack = NewObject<ULayerStack>();
        if (IsOverlay)
        {
            UOverlay* Overlay = WidgetTree->ConstructWidget<UOverlay>();
            UOverlaySlot* OverlaySlot = RootOverlay->AddChildToOverlay(Overlay);
            OverlaySlot->SetVerticalAlignment(VAlign_Fill);
            OverlaySlot->SetHorizontalAlignment(HAlign_Fill);

            LayerStack->InitializeAsOverlayStack(this, Overlay);
        }
        else
        {
            UCommonActivatableWidgetStack* Stack = WidgetTree->ConstructWidget<UCommonActivatableWidgetStack>();
            UOverlaySlot* OverlaySlot = RootOverlay->AddChildToOverlay(Stack);
            OverlaySlot->SetVerticalAlignment(VAlign_Fill);
            OverlaySlot->SetHorizontalAlignment(HAlign_Fill);

            LayerStack->InitializeAsStack(this, Stack);
        }

        LayerMap.Emplace(LayerTag, LayerStack);
    }
}
