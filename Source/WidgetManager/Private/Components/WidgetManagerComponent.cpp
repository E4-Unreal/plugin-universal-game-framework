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

    /* StartupWidgets */

    CreateStartupWidgets();
    ShowStartupWidgets();

    /* ToggleWidgets */

    CreateToggleWidgets();
    SetupInput();
    BindInput();
}

void UWidgetManagerComponent::OnComponentDestroyed(bool bDestroyingHierarchy)
{
    /* StartupWidgets */

    HideStartupWidgets();
    RemoveStartupWidgets();

    /* ToggleWidgets */

    RemoveToggleWidgets();
    UnBindInput();

    Super::OnComponentDestroyed(bDestroyingHierarchy);
}

void UWidgetManagerComponent::ShowWidget(UUserWidget* Widget)
{
    if (Widget && !Widget->IsInViewport())
    {
        Widget->AddToViewport();
    }
}

void UWidgetManagerComponent::HideWidget(UUserWidget* Widget)
{
    if (Widget && Widget->IsInViewport())
    {
        Widget->RemoveFromParent();
    }
}

void UWidgetManagerComponent::ToggleWidget(UUserWidget* Widget)
{
    if (Widget)
    {
        if (Widget->IsInViewport())
        {
            Widget->RemoveFromParent();
        }
        else
        {
            Widget->AddToViewport();
        }
    }
}

void UWidgetManagerComponent::CreateStartupWidgets()
{
    if (!StartupWidgets.IsEmpty()) return;

    StartupWidgets.Reserve(StartupWidgetClasses.Num());
    for (TSubclassOf<UUserWidget> StartupWidgetClass : StartupWidgetClasses)
    {
        if (StartupWidgetClass)
        {
            UUserWidget* StartupWidget = CreateWidget<UUserWidget>(GetWorld(), StartupWidgetClass);
            StartupWidgets.Emplace(StartupWidget);
        }
    }
}

void UWidgetManagerComponent::RemoveStartupWidgets()
{
    StartupWidgets.Empty();
}

void UWidgetManagerComponent::ShowStartupWidgets()
{
    for (UUserWidget* StartupWidget : StartupWidgets)
    {
        ShowWidget(StartupWidget);
    }
}

void UWidgetManagerComponent::HideStartupWidgets()
{
    for (UUserWidget* StartupWidget : StartupWidgets)
    {
        HideWidget(StartupWidget);
    }
}

void UWidgetManagerComponent::CreateToggleWidgets()
{
    if (!ToggleWidgetMap.IsEmpty()) return;

    ToggleWidgetMap.Reserve(ToggleWidgetClassMap.Num());
    for (const auto& [InputAction, ToggleWidgetClass] : ToggleWidgetClassMap)
    {
        if (InputAction && ToggleWidgetClass)
        {
            UUserWidget* ToggleWidget = CreateWidget<UUserWidget>(GetWorld(), ToggleWidgetClass);
            ToggleWidgetMap.Emplace(InputAction, ToggleWidget);
        }
    }
}

void UWidgetManagerComponent::RemoveToggleWidgets()
{
    for (const auto& [InputAction, ToggleWidget] : ToggleWidgetMap)
    {
        HideWidget(ToggleWidget);
    }

    ToggleWidgetMap.Empty();
}

UUserWidget* UWidgetManagerComponent::GetWidgetByInputAction(UInputAction* InputAction) const
{
    return ToggleWidgetMap.Contains(InputAction) ? ToggleWidgetMap[InputAction] : nullptr;
}

void UWidgetManagerComponent::SetupInput()
{
    EnhancedInputComponent = Cast<UEnhancedInputComponent>(GetOwner()->InputComponent);
}

void UWidgetManagerComponent::BindInput()
{
    if (EnhancedInputComponent.IsValid())
    {
        InputBindingHandleMap.Reserve(ToggleWidgetMap.Num());
        for (const auto& [InputAction, ToggleWidget] : ToggleWidgetMap)
        {
            FEnhancedInputActionEventBinding& EnhancedInputActionEventBinding = EnhancedInputComponent->BindAction(
                InputAction,
                ETriggerEvent::Triggered,
                this,
                &ThisClass::ToggleWidget,
                ToggleWidget.Get()
                );

            InputBindingHandleMap.Emplace(InputAction, EnhancedInputActionEventBinding.GetHandle());
        }
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
