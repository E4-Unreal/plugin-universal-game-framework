// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/PlayerWidgetManagerComponent.h"

#include "Blueprint/UserWidget.h"
#include "Interfaces/LayoutWidgetInterface.h"


UPlayerWidgetManagerComponent::UPlayerWidgetManagerComponent()
{
}

void UPlayerWidgetManagerComponent::BeginPlay()
{
    Super::BeginPlay();

    if (APlayerController* OwningPlayerController = GetOwningPlayerController())
    {
        if (LayoutWidgetClass)
        {
            LayoutWidget = CreateWidget<UUserWidget>(OwningPlayerController, LayoutWidgetClass);
            LayoutWidget->AddToViewport();
        }
    }
}

void UPlayerWidgetManagerComponent::OnComponentDestroyed(bool bDestroyingHierarchy)
{

    if (LayoutWidget)
    {
        LayoutWidget->RemoveFromParent();
    }

    Super::OnComponentDestroyed(bDestroyingHierarchy);
}

UUserWidget* UPlayerWidgetManagerComponent::ShowWidget(TSubclassOf<UUserWidget> WidgetClass)
{
    if (WidgetClass && LayoutWidget && LayoutWidget->Implements<ULayoutWidgetInterface>())
    {
        return ILayoutWidgetInterface::Execute_ShowWidget(LayoutWidget, WidgetClass);
    }

    return nullptr;
}

bool UPlayerWidgetManagerComponent::HideWidget(TSubclassOf<UUserWidget> WidgetClass)
{
    if (WidgetClass && LayoutWidget && LayoutWidget->Implements<ULayoutWidgetInterface>())
    {
        return ILayoutWidgetInterface::Execute_HideWidget(LayoutWidget, WidgetClass);
    }

    return false;
}

void UPlayerWidgetManagerComponent::ToggleWidget(TSubclassOf<UUserWidget> WidgetClass)
{
    if (WidgetClass && LayoutWidget && LayoutWidget->Implements<ULayoutWidgetInterface>())
    {
        ILayoutWidgetInterface::Execute_ToggleWidget(LayoutWidget, WidgetClass);
    }
}

void UPlayerWidgetManagerComponent::ExecuteBackAction()
{
    if (LayoutWidget && LayoutWidget->Implements<ULayoutWidgetInterface>())
    {
        ILayoutWidgetInterface::Execute_ExecuteBackAction(LayoutWidget);
    }
}

APlayerController* UPlayerWidgetManagerComponent::GetOwningPlayerController() const
{
    APlayerController* PlayerController = CastChecked<APlayerController>(GetOwner());

    return PlayerController->IsLocalController() ? PlayerController : nullptr;
}
