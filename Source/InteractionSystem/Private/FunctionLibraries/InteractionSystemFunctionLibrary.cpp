// Fill out your copyright notice in the Description page of Project Settings.


#include "FunctionLibraries/InteractionSystemFunctionLibrary.h"

#include "Blueprint/UserWidget.h"
#include "Interfaces/InteractableInterface.h"
#include "Interfaces/InteractionWidgetInterface.h"

UObject* UInteractionSystemFunctionLibrary::GetInteractableObject(AActor* TargetActor)
{
    UObject* InteractableObject = nullptr;

    if (TargetActor)
    {
        if (TargetActor->Implements<UInteractableInterface>())
        {
            InteractableObject = TargetActor;
        }
        else
        {
            InteractableObject = TargetActor->FindComponentByInterface<UInteractableInterface>();
        }
    }

    return InteractableObject;
}

bool UInteractionSystemFunctionLibrary::IsInteractable(AActor* TargetActor)
{
    return GetInteractableObject(TargetActor) != nullptr;
}

FGameplayTag UInteractionSystemFunctionLibrary::GetInteractionType(AActor* TargetActor)
{
    if (auto InteractableObject = GetInteractableObject(TargetActor))
    {
        return IInteractableInterface::Execute_GetInteractionType(InteractableObject);
    }

    return FGameplayTag::EmptyTag;
}

FText UInteractionSystemFunctionLibrary::GetInteractionMessage(AActor* TargetActor)
{
    if (auto InteractableObject = GetInteractableObject(TargetActor))
    {
        return IInteractableInterface::Execute_GetInteractionMessage(InteractableObject);
    }

    return FText::GetEmpty();
}

bool UInteractionSystemFunctionLibrary::IsInteracting(AActor* TargetActor)
{
    return GetInteractor(TargetActor) != nullptr;
}

AActor* UInteractionSystemFunctionLibrary::GetInteractor(AActor* TargetActor)
{
    if (auto InteractableObject = GetInteractableObject(TargetActor))
    {
        return IInteractableInterface::Execute_GetInteractor(InteractableObject);
    }

    return nullptr;
}

bool UInteractionSystemFunctionLibrary::CanInteract(AActor* TargetActor, AActor* Interactor)
{
    if (auto InteractableObject = GetInteractableObject(TargetActor))
    {
        return IInteractableInterface::Execute_CanInteract(InteractableObject, Interactor);
    }

    return false;
}

void UInteractionSystemFunctionLibrary::Interact(AActor* TargetActor, AActor* Interactor)
{
    if (auto InteractableObject = GetInteractableObject(TargetActor))
    {
        IInteractableInterface::Execute_Interact(InteractableObject, Interactor);
    }
}

void UInteractionSystemFunctionLibrary::CancelInteract(AActor* TargetActor, AActor* Interactor)
{
    if (auto InteractableObject = GetInteractableObject(TargetActor))
    {
        IInteractableInterface::Execute_CancelInteract(InteractableObject, Interactor);
    }
}

bool UInteractionSystemFunctionLibrary::CanSelect(AActor* TargetActor, AActor* Interactor)
{
    if (auto InteractableObject = GetInteractableObject(TargetActor))
    {
        return IInteractableInterface::Execute_CanSelect(InteractableObject, Interactor);
    }

    return false;
}

void UInteractionSystemFunctionLibrary::Select(AActor* TargetActor, AActor* Interactor)
{
    if (auto InteractableObject = GetInteractableObject(TargetActor))
    {
        IInteractableInterface::Execute_Select(InteractableObject, Interactor);
    }
}

void UInteractionSystemFunctionLibrary::Deselect(AActor* TargetActor, AActor* Interactor)
{
    if (auto InteractableObject = GetInteractableObject(TargetActor))
    {
        IInteractableInterface::Execute_Deselect(InteractableObject, Interactor);
    }
}

bool UInteractionSystemFunctionLibrary::IsInteractionWidget(UUserWidget* Widget)
{
    return Widget && Widget->Implements<UInteractionWidgetInterface>();
}

void UInteractionSystemFunctionLibrary::SetInteractionType(UUserWidget* Widget, FGameplayTag NewInteractionType)
{
    if (IsInteractionWidget(Widget))
    {
        IInteractionWidgetInterface::Execute_SetInteractionType(Widget, NewInteractionType);
    }
}

void UInteractionSystemFunctionLibrary::SetInteractionMessage(UUserWidget* Widget, const FText& NewInteractionMessage)
{
    if (IsInteractionWidget(Widget))
    {
        IInteractionWidgetInterface::Execute_SetInteractionMessage(Widget, NewInteractionMessage);
    }
}
