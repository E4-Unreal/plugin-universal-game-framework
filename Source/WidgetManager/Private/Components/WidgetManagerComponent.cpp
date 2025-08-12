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

    CreateToggleableWidgets();
    CreateEscapeMenuWidget();
    SetupInput();
    BindInput();
}

void UWidgetManagerComponent::OnComponentDestroyed(bool bDestroyingHierarchy)
{
    RemoveToggleableWidgets();
    RemoveEscapeMenuWidget();
    UnBindInput();

    Super::OnComponentDestroyed(bDestroyingHierarchy);
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

void UWidgetManagerComponent::CreateToggleableWidgets()
{
    if (!ToggleableWidgetMap.IsEmpty()) return;

    ToggleableWidgetMap.Reserve(ToggleableWidgetClassMap.Num());
    for (const auto& [InputAction, ToggleWidgetClass] : ToggleableWidgetClassMap)
    {
        if (InputAction && ToggleWidgetClass)
        {
            UUserWidget* ToggleWidget = CreateWidget<UUserWidget>(GetWorld(), ToggleWidgetClass);
            ToggleableWidgetMap.Emplace(InputAction, ToggleWidget);
        }
    }
}

void UWidgetManagerComponent::RemoveToggleableWidgets()
{
    for (const auto& [InputAction, ToggleWidget] : ToggleableWidgetMap)
    {
        HideWidgetByAction(InputAction);
    }

    ToggleableWidgetMap.Empty();
}

void UWidgetManagerComponent::SetupInput()
{
    EnhancedInputComponent = Cast<UEnhancedInputComponent>(GetOwner()->InputComponent);
}

void UWidgetManagerComponent::BindInput()
{
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
                &ThisClass::HideTopWidget
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

void UWidgetManagerComponent::CreateEscapeMenuWidget()
{
    if (EscapeMenuWidgetClass && !EscapeMenuWidget)
    {
        EscapeMenuWidget = CreateWidget<UUserWidget>(GetWorld(), EscapeMenuWidgetClass);
    }
}

void UWidgetManagerComponent::RemoveEscapeMenuWidget()
{
    HideWidget(EscapeMenuWidget);
    EscapeMenuWidget = nullptr;
}

void UWidgetManagerComponent::ShowEscapeMenu()
{
    ShowWidget(EscapeMenuWidget);
}

void UWidgetManagerComponent::HideEscapeMenu()
{
    HideWidget(EscapeMenuWidget);
}
