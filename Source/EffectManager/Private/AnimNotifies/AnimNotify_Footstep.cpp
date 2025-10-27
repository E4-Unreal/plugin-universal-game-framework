// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimNotifies/AnimNotify_Footstep.h"

#include "Components/FootstepManagerComponent.h"

UAnimNotify_Footstep::UAnimNotify_Footstep()
{
    SocketName = "root";
}

void UAnimNotify_Footstep::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
    const FAnimNotifyEventReference& EventReference)
{
    Super::Notify(MeshComp, Animation, EventReference);

    if (auto Owner = MeshComp->GetOwner())
    {
        if (auto FootstepManager = Owner->GetComponentByClass<UFootstepManagerComponent>())
        {
            FootstepManager->SpawnEffect(SocketName);
        }
    }
}
