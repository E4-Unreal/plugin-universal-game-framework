// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/InteractionWidgetBase.h"

#include "Components/TextBlock.h"
#include "GameplayTags/InteractionGameplaytags.h"

UInteractionWidgetBase::UInteractionWidgetBase(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer)
{
    InteractionTypeTextMap.Emplace(Interaction::Root, NSLOCTEXT("InteractionSystem", "Interact", "Interact"));
    InteractionTypeTextMap.Emplace(Interaction::Talk, NSLOCTEXT("InteractionSystem", "Talk", "Talk"));
}

void UInteractionWidgetBase::SetInteractionType_Implementation(FGameplayTag NewInteractionType)
{
    if (!InteractionTypeTextMap.Contains(NewInteractionType)) NewInteractionType = Interaction::Root;

    SetInteractionTypeText(InteractionTypeTextMap.FindRef(NewInteractionType));
}

void UInteractionWidgetBase::SetInteractionMessage_Implementation(const FText& NewInteractionMessage)
{
    SetInteractionMessageText(NewInteractionMessage);
}

void UInteractionWidgetBase::SetInteractionTypeText(const FText& NewInteractionTypeText)
{
    if (GetInteractionTypeTextBlock())
    {
        GetInteractionTypeTextBlock()->SetText(NewInteractionTypeText);
    }
}

void UInteractionWidgetBase::SetInteractionMessageText(const FText& NewInteractionMessageText)
{
    if (GetInteractionMessageTextBlock())
    {
        GetInteractionMessageTextBlock()->SetText(NewInteractionMessageText);
    }
}
