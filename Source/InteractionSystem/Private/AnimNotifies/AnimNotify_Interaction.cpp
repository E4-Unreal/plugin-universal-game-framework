// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimNotifies/AnimNotify_Interaction.h"

#include "Components/InteractionSystemComponent.h"
#include "Interfaces/InteractableInterface.h"

void UAnimNotify_Interaction::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
                                     const FAnimNotifyEventReference& EventReference)
{
    Super::Notify(MeshComp, Animation, EventReference);

    if (auto Owner = MeshComp->GetOwner())
    {
        if (auto InteractionSystem = Owner->GetComponentByClass<UInteractionSystemComponent>())
        {
            const auto& SelectedTargets = InteractionSystem->GetSelectedTargets();
            for (const auto& SelectedTarget : SelectedTargets)
            {
                if (SelectedTarget && SelectedTarget->Implements<UInteractableInterface>() && IInteractableInterface::Execute_CanInteract(SelectedTarget, Owner))
                {
                    const auto& TargetInteractionType = IInteractableInterface::Execute_GetInteractionType(SelectedTarget);
                    if (TargetInteractionType == InteractionType)
                    {
                        IInteractableInterface::Execute_Interact(SelectedTarget, Owner);
                    }
                }
            }
        }
    }
}
