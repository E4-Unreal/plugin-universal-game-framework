// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/CommonLayoutWidgetBase.h"

#include "Components/Overlay.h"
#include "Components/OverlaySlot.h"
#include "Interfaces/LayerWidgetInterface.h"
#include "Objects/LayerStack.h"
#include "Widgets/CommonActivatableWidgetContainer.h"
#include "Widgets/CustomActivatableWidgetStack.h"
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
                Execute_ToggleWidget(this, EscapeMenuWidgetClass);
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

UUserWidget* UCommonLayoutWidgetBase::ShowWidget_Implementation(TSubclassOf<UUserWidget> WidgetClass)
{
    if (WidgetClass == nullptr) return nullptr;

    if (WidgetClass->ImplementsInterface(ULayerWidgetInterface::StaticClass()))
    {
        FGameplayTag LayerTag = ILayerWidgetInterface::Execute_GetLayerTag(WidgetClass->GetDefaultObject());
        if (ULayerStack* Layer = GetLayer(LayerTag))
        {
            return Layer->ShowWidget(WidgetClass.Get());
        }
    }

    return nullptr;
}

bool UCommonLayoutWidgetBase::HideWidget_Implementation(TSubclassOf<UUserWidget> WidgetClass)
{
    if (WidgetClass == nullptr) return false;

    if (WidgetClass->ImplementsInterface(ULayerWidgetInterface::StaticClass()))
    {
        FGameplayTag LayerTag = ILayerWidgetInterface::Execute_GetLayerTag(WidgetClass->GetDefaultObject());
        if (ULayerStack* Layer = GetLayer(LayerTag))
        {
            return Layer->HideWidget(WidgetClass.Get());
        }
    }

    return false;
}

void UCommonLayoutWidgetBase::ToggleWidget_Implementation(TSubclassOf<UUserWidget> WidgetClass)
{
    if (WidgetClass == nullptr) return;

    if (WidgetClass->ImplementsInterface(ULayerWidgetInterface::StaticClass()))
    {
        FGameplayTag LayerTag = ILayerWidgetInterface::Execute_GetLayerTag(WidgetClass->GetDefaultObject());
        if (ULayerStack* Layer = GetLayer(LayerTag))
        {
            return Layer->ToggleWidget(WidgetClass.Get());
        }
    }
}

void UCommonLayoutWidgetBase::ExecuteBackAction_Implementation()
{
    // NativeOnHandleBackAction에서 BackAction 자체 처리
}

void UCommonLayoutWidgetBase::CreateLayerMap()
{
    if (!LayerMap.IsEmpty()) return;

    for (const auto& [LayerTag, LayerConfig] : LayerConfigs)
    {
        ULayerStack* LayerStack = NewObject<ULayerStack>();
        if (LayerConfig.bIsOverlay)
        {
            UOverlay* Overlay = WidgetTree->ConstructWidget<UOverlay>();
            UOverlaySlot* OverlaySlot = RootOverlay->AddChildToOverlay(Overlay);
            OverlaySlot->SetVerticalAlignment(VAlign_Fill);
            OverlaySlot->SetHorizontalAlignment(HAlign_Fill);

            LayerStack->InitializeAsOverlayStack(this, Overlay, LayerConfig.TransitionConfig);
        }
        else
        {
            UCustomActivatableWidgetStack* Stack = WidgetTree->ConstructWidget<UCustomActivatableWidgetStack>();
            Stack->SetTransitionConfig(LayerConfig.TransitionConfig);
            UOverlaySlot* OverlaySlot = RootOverlay->AddChildToOverlay(Stack);
            OverlaySlot->SetVerticalAlignment(VAlign_Fill);
            OverlaySlot->SetHorizontalAlignment(HAlign_Fill);

            LayerStack->InitializeAsStack(this, Stack);
        }

        LayerMap.Emplace(LayerTag, LayerStack);
    }
}
