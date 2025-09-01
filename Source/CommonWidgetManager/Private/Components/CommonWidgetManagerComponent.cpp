// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/CommonWidgetManagerComponent.h"

#include "Blueprint/UserWidget.h"
#include "Widgets/CommonLayoutWidgetBase.h"

void UCommonWidgetManagerComponent::BeginPlay()
{
    Super::BeginPlay();

    if (APlayerController* OwningPlayerController = GetOwningPlayerController())
    {
        if (LayoutWidgetClass)
        {
            LayoutWidget = CreateWidget<UCommonLayoutWidgetBase>(OwningPlayerController, LayoutWidgetClass);
            LayoutWidget->AddToViewport();
        }
    }
}

void UCommonWidgetManagerComponent::OnComponentDestroyed(bool bDestroyingHierarchy)
{
    if (LayoutWidget)
    {
        LayoutWidget->RemoveFromParent();
    }

    Super::OnComponentDestroyed(bDestroyingHierarchy);
}

APlayerController* UCommonWidgetManagerComponent::GetOwningPlayerController() const
{
    APlayerController* OwningPlayerController = nullptr;
    if (AActor* OwningActor = GetOwner())
    {
        if (OwningActor->IsA(APlayerController::StaticClass()))
        {
            OwningPlayerController = Cast<APlayerController>(OwningActor);
        }
        else if (OwningActor->IsA(APawn::StaticClass()))
        {
            APawn* OwningPawn = Cast<APawn>(OwningActor);
            OwningPlayerController = Cast<APlayerController>(OwningPawn->GetController());
        }

        if (OwningPlayerController && !OwningPlayerController->IsLocalController())
        {
            OwningPlayerController = nullptr;
        }
    }

    return OwningPlayerController;
}
