// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/InteractionWidgetBase.h"

#include "Components/TextBlock.h"
#include "GameplayTags/InteractionGameplaytags.h"
#include "Internationalization/StringTableRegistry.h"

UInteractionWidgetBase::UInteractionWidgetBase(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer)
{
    InteractionTypeTextMap.Emplace(Interaction::Root, LOCTABLE("Interaction", "Interact"));
    InteractionTypeTextMap.Emplace(Interaction::Open, LOCTABLE("Interaction", "Open"));
    InteractionTypeTextMap.Emplace(Interaction::Pickup, LOCTABLE("Interaction", "Pickup"));
    InteractionTypeTextMap.Emplace(Interaction::Talk, LOCTABLE("Interaction", "Talk"));
    InteractionTypeTextMap.Emplace(Interaction::Move, LOCTABLE("Interaction", "Move"));

    InteractionTypeTextMap.Emplace(Interaction::Woodcutting, LOCTABLE("Interaction", "Woodcutting"));
    InteractionTypeTextMap.Emplace(Interaction::Mining, LOCTABLE("Interaction", "Mining"));
    InteractionTypeTextMap.Emplace(Interaction::Fishing, LOCTABLE("Interaction", "Fishing"));
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
