// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/WidgetManagerComponent.h"

#include "EnhancedInputComponent.h"
#include "Blueprint/UserWidget.h"


UWidgetManagerComponent::UWidgetManagerComponent(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer)
{
}

void UWidgetManagerComponent::BeginPlay()
{
    Super::BeginPlay();

    BindInput();
}

void UWidgetManagerComponent::OnComponentDestroyed(bool bDestroyingHierarchy)
{
    UnBindInput();

    Super::OnComponentDestroyed(bDestroyingHierarchy);
}

bool UWidgetManagerComponent::ShowPanelWidget(TSubclassOf<UUserWidget> PanelWidgetClass)
{
    if (ShowWidgetByClass(PanelWidgetClass))
    {
        UUserWidget* PanelWidget = GetOrCreateWidgetByClass(PanelWidgetClass);
        PanelWidgets.Emplace(PanelWidget);

        return true;
    }

    return false;
}

bool UWidgetManagerComponent::HidePanelWidget(TSubclassOf<UUserWidget> PanelWidgetClass)
{
    if (HideWidgetByClass(PanelWidgetClass))
    {
        UUserWidget* PanelWidget = GetOrCreateWidgetByClass(PanelWidgetClass);
        PanelWidgets.RemoveSingle(PanelWidget);

        return true;
    }

    return false;
}

void UWidgetManagerComponent::TogglePanelWidget(TSubclassOf<UUserWidget> PanelWidgetClass)
{
    if (ShowPanelWidget(PanelWidgetClass)) return;

    HidePanelWidget(PanelWidgetClass);
}

void UWidgetManagerComponent::CreateWidgets()
{
    Super::CreateWidgets();

    CreatePanelWidgets();
    CreateEscapeMenuWidget();
}

void UWidgetManagerComponent::DestroyWidgets()
{
    Super::DestroyWidgets();

    DestroyPanelWidgets();
    DestroyEscapeMenuWidget();
}

void UWidgetManagerComponent::BindInput()
{
    EnhancedInputComponent = Cast<UEnhancedInputComponent>(GetOwner()->InputComponent);
    if (EnhancedInputComponent.IsValid())
    {
        // Toggle

        InputBindingHandleMap.Reserve(PanelWidgetClassMap.Num());
        for (const auto& [InputAction, PanelWidgetClass] : PanelWidgetClassMap)
        {
            FEnhancedInputActionEventBinding& ToggleActionEventBinding = EnhancedInputComponent->BindAction(
                InputAction,
                ETriggerEvent::Triggered,
                this,
                &ThisClass::ToggleWidgetByAction,
                InputAction.Get()
                );

            InputBindingHandleMap.Emplace(InputAction, ToggleActionEventBinding.GetHandle());
        }

        // Escape

        FEnhancedInputActionEventBinding& EscapeActionEventBinding = EnhancedInputComponent->BindAction(
                EscapeAction,
                ETriggerEvent::Triggered,
                this,
                &ThisClass::OnEscapeActionTriggered
                );

        InputBindingHandleMap.Emplace(EscapeAction, EscapeActionEventBinding.GetHandle());
    }
}

void UWidgetManagerComponent::UnBindInput()
{
    if (EnhancedInputComponent.IsValid())
    {
        for (const auto& [InputAction, InputBindingHandle] : InputBindingHandleMap)
        {
            EnhancedInputComponent->RemoveActionBindingForHandle(InputBindingHandle);
        }
    }

    InputBindingHandleMap.Empty();
}

void UWidgetManagerComponent::OnEscapeActionTriggered()
{
    if (PanelWidgets.IsEmpty())
    {
        ToggleEscapeMenu();
    }
    else
    {
        HideTopWidget();
    }
}

void UWidgetManagerComponent::CreatePanelWidgets()
{
    for (const auto& [InputAction, PanelWidgetClass] : PanelWidgetClassMap)
    {
        UUserWidget* PanelWidget = GetOrCreateWidgetByClass(PanelWidgetClass);
    }
}

void UWidgetManagerComponent::DestroyPanelWidgets()
{
    for (const auto& [InputAction, PanelWidgetClass] : PanelWidgetClassMap)
    {
        DestroyWidgetByClass(PanelWidgetClass);
    }
}

TSubclassOf<UUserWidget> UWidgetManagerComponent::GetWidgetClassByAction(UInputAction* InputAction) const
{
    return PanelWidgetClassMap.Contains(InputAction) ? PanelWidgetClassMap[InputAction] : nullptr;
}

bool UWidgetManagerComponent::ShowWidgetByAction(UInputAction* InputAction)
{
    TSubclassOf<UUserWidget> PanelWidgetClass = GetWidgetClassByAction(InputAction);

    return ShowPanelWidget(PanelWidgetClass);
}

bool UWidgetManagerComponent::HideWidgetByAction(UInputAction* InputAction)
{
    TSubclassOf<UUserWidget> PanelWidgetClass = GetWidgetClassByAction(InputAction);

    return HidePanelWidget(PanelWidgetClass);
}

void UWidgetManagerComponent::ToggleWidgetByAction(UInputAction* InputAction)
{
    if (ShowWidgetByAction(InputAction)) return;

    HideWidgetByAction(InputAction);
}

void UWidgetManagerComponent::HideTopWidget()
{
    if (PanelWidgets.IsEmpty()) return;

    UUserWidget* TopWidget = PanelWidgets.Pop();
    HideWidget(TopWidget);
}

void UWidgetManagerComponent::CreateEscapeMenuWidget()
{
    if (EscapeMenuWidget) return;
    EscapeMenuWidget = CreateWidgetByClass(EscapeMenuWidgetClass);
}

void UWidgetManagerComponent::DestroyEscapeMenuWidget()
{
    HideWidget(EscapeMenuWidget);
    EscapeMenuWidget = nullptr;
}

bool UWidgetManagerComponent::ShowEscapeMenu()
{
    if (ShowWidget(EscapeMenuWidget))
    {
        if (APlayerController* OwningPlayerController = GetOwningPlayerController())
        {
            OwningPlayerController->SetIgnoreMoveInput(true);
            OwningPlayerController->SetIgnoreLookInput(true);
        }

        return true;
    }

    return false;
}

bool UWidgetManagerComponent::HideEscapeMenu()
{
    if (HideWidget(EscapeMenuWidget))
    {
        if (APlayerController* OwningPlayerController = GetOwningPlayerController())
        {
            OwningPlayerController->SetIgnoreMoveInput(false);
            OwningPlayerController->SetIgnoreLookInput(false);
        }

        return true;
    }

    return false;
}

void UWidgetManagerComponent::ToggleEscapeMenu()
{
    if (ShowEscapeMenu()) return;

    HideEscapeMenu();
}
