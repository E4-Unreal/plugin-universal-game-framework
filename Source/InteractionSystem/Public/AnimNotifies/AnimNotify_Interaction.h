// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "AnimNotify_Interaction.generated.h"

/**
 *
 */
UCLASS()
class INTERACTIONSYSTEM_API UAnimNotify_Interaction : public UAnimNotify
{
    GENERATED_BODY()

public:
    /* AnimNotify */

    virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override;
};
