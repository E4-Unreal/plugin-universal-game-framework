// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/WidgetManagerComponentBase.h"

#include "Blueprint/UserWidget.h"

UWidgetManagerComponentBase::UWidgetManagerComponentBase(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer)
{
}

void UWidgetManagerComponentBase::BeginPlay()
{
    Super::BeginPlay();

    CreateWidgets();
    ShowStartupWidgets();
}

void UWidgetManagerComponentBase::OnComponentDestroyed(bool bDestroyingHierarchy)
{
    DestroyWidgets();

    Super::OnComponentDestroyed(bDestroyingHierarchy);
}

APlayerController* UWidgetManagerComponentBase::GetOwningPlayerController() const
{
    UClass* OwnerClass = GetOwner()->GetClass();
    APlayerController* OwningPlayerController = nullptr;
    if (OwnerClass->IsChildOf<APlayerController>())
    {
        OwningPlayerController = Cast<APlayerController>(GetOwner());
    }
    else if (OwnerClass->IsChildOf<APawn>())
    {
        APawn* OwningPawn = Cast<APawn>(GetOwner());
        OwningPlayerController = Cast<APlayerController>(OwningPawn->GetController());
    }

    return OwningPlayerController;
}

UUserWidget* UWidgetManagerComponentBase::CreateWidgetByClass(TSubclassOf<UUserWidget> WidgetClass)
{
    if (!WidgetClass) return nullptr;

    APlayerController* OwningPlayerController = GetOwningPlayerController();
    if (!OwningPlayerController) return nullptr;

    return CreateWidget<UUserWidget>(OwningPlayerController, WidgetClass);
}

bool UWidgetManagerComponentBase::ShowWidget(UUserWidget* Widget)
{
    if (Widget && !Widget->IsInViewport())
    {
        Widget->AddToViewport();
        return true;
    }

    return false;
}

bool UWidgetManagerComponentBase::HideWidget(UUserWidget* Widget)
{
    if (Widget && Widget->IsInViewport())
    {
        Widget->RemoveFromParent();
        return true;
    }

    return false;
}

void UWidgetManagerComponentBase::ToggleWidget(UUserWidget* Widget)
{
    if (ShowWidget(Widget)) return;

    HideWidget(Widget);
}

void UWidgetManagerComponentBase::CreateWidgets()
{
    CreateStartupWidgets();
}

void UWidgetManagerComponentBase::DestroyWidgets()
{
    DestroyStartupWidgets();
}

void UWidgetManagerComponentBase::CreateStartupWidgets()
{
    if (!StartupWidgets.IsEmpty()) return;

    StartupWidgets.Reserve(StartupWidgetClasses.Num());
    for (TSubclassOf<UUserWidget> StartupWidgetClass : StartupWidgetClasses)
    {
        if (UUserWidget* StartupWidget = CreateWidgetByClass(StartupWidgetClass))
        {
            StartupWidgets.Emplace(StartupWidget);
        }
    }
}

void UWidgetManagerComponentBase::DestroyStartupWidgets()
{
    HideStartupWidgets();
    StartupWidgets.Empty();
}

void UWidgetManagerComponentBase::ShowStartupWidgets()
{
    for (UUserWidget* StartupWidget : StartupWidgets)
    {
        ShowWidget(StartupWidget);
    }
}

void UWidgetManagerComponentBase::HideStartupWidgets()
{
    for (UUserWidget* StartupWidget : StartupWidgets)
    {
        HideWidget(StartupWidget);
    }
}

void UWidgetManagerComponentBase::ToggleStartupWidgets()
{
    for (UUserWidget* StartupWidget : StartupWidgets)
    {
        ToggleWidget(StartupWidget);
    }
}
