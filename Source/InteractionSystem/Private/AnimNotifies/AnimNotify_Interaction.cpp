// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimNotifies/AnimNotify_Interaction.h"

#include "Components/InteractionSystemComponent.h"

UAnimNotify_Interaction::UAnimNotify_Interaction()
{
    bLoop = true;
    LoopSectionName = FName("Loop");
    EndSectionName = FName("End");
}

void UAnimNotify_Interaction::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
                                     const FAnimNotifyEventReference& EventReference)
{
    Super::Notify(MeshComp, Animation, EventReference);

    if (auto Owner = MeshComp->GetOwner())
    {
        if (auto InteractionSystem = Owner->GetComponentByClass<UInteractionSystemComponent>())
        {
            // 현재 선택된 상호작용 종류가 애니메이션의 상호작용 종류와 일치할 경우 상호작용 실행
            if (InteractionSystem->GetSelectedInteractionType() == InteractionType)
            {
                InteractionSystem->TryInteract();
            }

            // 더이상 일치하지 않을 경우 애니메이션 종료
            FName CurrentSectionName = MeshComp->GetAnimInstance()->Montage_GetCurrentSection();
            FName NextSectionName = bLoop && InteractionSystem->GetSelectedInteractionType() == InteractionType ? LoopSectionName : EndSectionName;
            MeshComp->GetAnimInstance()->Montage_SetNextSection(CurrentSectionName, NextSectionName);
        }
    }
}
