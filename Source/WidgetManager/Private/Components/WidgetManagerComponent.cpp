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

    CreateStartupWidgets();
    ShowStartupWidgets();

    CreateToggleWidgets();

    SetupInput();
    BindInput();
}

void UWidgetManagerComponent::OnComponentDestroyed(bool bDestroyingHierarchy)
{
    HideStartupWidgets();
    RemoveStartupWidgets();

    HideToggleWidgets();
    RemoveToggleWidgets();

    UnBindInput();

    Super::OnComponentDestroyed(bDestroyingHierarchy);
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
        if (StartupWidget && !StartupWidget->IsInViewport())
        {
            StartupWidget->AddToViewport();
        }
    }
}

void UWidgetManagerComponent::HideStartupWidgets()
{
    for (UUserWidget* StartupWidget : StartupWidgets)
    {
        if (StartupWidget && StartupWidget->IsInViewport())
        {
            StartupWidget->RemoveFromParent();
        }
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
    ToggleWidgetMap.Empty();
}

UUserWidget* UWidgetManagerComponent::GetWidgetByInputAction(UInputAction* InputAction) const
{
    return ToggleWidgetMap.Contains(InputAction) ? ToggleWidgetMap[InputAction] : nullptr;
}

void UWidgetManagerComponent::ToggleWidgetByInputAction(UInputAction* InputAction)
{
    if (UUserWidget* ToggleWidget = GetWidgetByInputAction(InputAction))
    {
        if (ToggleWidget->IsInViewport())
        {
            ToggleWidget->RemoveFromParent();
        }
        else
        {
            ToggleWidget->AddToViewport();
        }
    }
}

void UWidgetManagerComponent::ShowWidgetByInputAction(UInputAction* InputAction)
{
    if (UUserWidget* ToggleWidget = GetWidgetByInputAction(InputAction))
    {
        if (!ToggleWidget->IsInViewport())
        {
            ToggleWidget->AddToViewport();
        }
    }
}

void UWidgetManagerComponent::HideWidgetByInputAction(UInputAction* InputAction)
{
    if (UUserWidget* ToggleWidget = GetWidgetByInputAction(InputAction))
    {
        if (ToggleWidget->IsInViewport())
        {
            ToggleWidget->RemoveFromParent();
        }
    }
}

void UWidgetManagerComponent::HideToggleWidgets()
{
    for (const auto& [InputAction, ToggleWidget] : ToggleWidgetMap)
    {
        HideWidgetByInputAction(InputAction);
    }
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
                &ThisClass::ToggleWidgetByInputAction,
                InputAction.Get()
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
