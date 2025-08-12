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

void UWidgetManagerComponent::CreateWidgets()
{
    Super::CreateWidgets();

    CreateToggleableWidgets();
    CreateEscapeMenuWidget();
}

void UWidgetManagerComponent::DestroyWidgets()
{
    Super::DestroyWidgets();

    DestroyToggleableWidgets();
    DestroyEscapeMenuWidget();
}

void UWidgetManagerComponent::BindInput()
{
    EnhancedInputComponent = Cast<UEnhancedInputComponent>(GetOwner()->InputComponent);
    if (EnhancedInputComponent.IsValid())
    {
        // Toggle

        InputBindingHandleMap.Reserve(ToggleableWidgetMap.Num());
        for (const auto& [InputAction, ToggleWidget] : ToggleableWidgetMap)
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
    if (ToggleableWidgetStack.IsEmpty())
    {
        ToggleEscapeMenu();
    }
    else
    {
        HideTopWidget();
    }
}

void UWidgetManagerComponent::CreateToggleableWidgets()
{
    if (!ToggleableWidgetMap.IsEmpty()) return;

    ToggleableWidgetMap.Reserve(ToggleableWidgetClassMap.Num());
    for (const auto& [InputAction, ToggleWidgetClass] : ToggleableWidgetClassMap)
    {
        if (InputAction && ToggleWidgetClass)
        {
            if (UUserWidget* ToggleWidget = CreateWidgetByClass(ToggleWidgetClass))
            {
                ToggleableWidgetMap.Emplace(InputAction, ToggleWidget);
            }
        }
    }
}

void UWidgetManagerComponent::DestroyToggleableWidgets()
{
    for (const auto& [InputAction, ToggleWidget] : ToggleableWidgetMap)
    {
        HideWidgetByAction(InputAction);
    }

    ToggleableWidgetMap.Empty();
}

UUserWidget* UWidgetManagerComponent::GetWidgetByAction(UInputAction* InputAction) const
{
    return ToggleableWidgetMap.Contains(InputAction) ? ToggleableWidgetMap[InputAction] : nullptr;
}

void UWidgetManagerComponent::ShowWidgetByAction(UInputAction* InputAction)
{
    if (UUserWidget* ToggleableWidget = GetWidgetByAction(InputAction))
    {
        if (!ToggleableWidgetStack.Contains(ToggleableWidget))
        {
            ToggleableWidgetStack.Emplace(ToggleableWidget);
            ShowWidget(ToggleableWidget);
        }
    }
}

void UWidgetManagerComponent::HideWidgetByAction(UInputAction* InputAction)
{
    if (UUserWidget* ToggleableWidget = GetWidgetByAction(InputAction))
    {
        if (ToggleableWidgetStack.Contains(ToggleableWidget))
        {
            ToggleableWidgetStack.RemoveSingle(ToggleableWidget);
            HideWidget(ToggleableWidget);
        }
    }
}

void UWidgetManagerComponent::ToggleWidgetByAction(UInputAction* InputAction)
{
    if (UUserWidget* ToggleableWidget = GetWidgetByAction(InputAction))
    {
        if (!ToggleableWidgetStack.Contains(ToggleableWidget))
        {
            ToggleableWidgetStack.Emplace(ToggleableWidget);
            ShowWidget(ToggleableWidget);
        }
        else
        {
            ToggleableWidgetStack.RemoveSingle(ToggleableWidget);
            HideWidget(ToggleableWidget);
        }
    }
}

void UWidgetManagerComponent::HideTopWidget()
{
    if (ToggleableWidgetStack.IsEmpty()) return;

    UUserWidget* TopWidget = ToggleableWidgetStack.Pop();
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

void UWidgetManagerComponent::ShowEscapeMenu()
{
    if (ShowWidget(EscapeMenuWidget))
    {
        if (APlayerController* OwningPlayerController = GetOwningPlayerController())
        {
            OwningPlayerController->SetIgnoreMoveInput(true);
            OwningPlayerController->SetIgnoreLookInput(true);
        }
    }
}

void UWidgetManagerComponent::HideEscapeMenu()
{
    if (HideWidget(EscapeMenuWidget))
    {
        if (APlayerController* OwningPlayerController = GetOwningPlayerController())
        {
            OwningPlayerController->SetIgnoreMoveInput(false);
            OwningPlayerController->SetIgnoreLookInput(false);
        }
    }
}

void UWidgetManagerComponent::ToggleEscapeMenu()
{
    ToggleWidget(EscapeMenuWidget);
}
