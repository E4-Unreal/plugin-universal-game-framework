// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimNotifies/AnimNotify_Interaction.h"

#include "Components/InteractionSystemComponent.h"

void UAnimNotify_Interaction::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
                                     const FAnimNotifyEventReference& EventReference)
{
    Super::Notify(MeshComp, Animation, EventReference);

    if (auto Owner = MeshComp->GetOwner())
    {
        if (auto InteractionSystem = Owner->GetComponentByClass<UInteractionSystemComponent>())
        {
            InteractionSystem->TryInteract();
        }
    }
}
