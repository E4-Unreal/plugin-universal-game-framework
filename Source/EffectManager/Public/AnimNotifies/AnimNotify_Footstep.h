// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "AnimNotify_Footstep.generated.h"

/**
 *
 */
UCLASS(Meta = (DisplayName = "Footstep"))
class EFFECTMANAGER_API UAnimNotify_Footstep : public UAnimNotify
{
    GENERATED_BODY()

protected:
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FName SocketName;

public:
    UAnimNotify_Footstep();

    /* AnimNotify */

    virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override;
};
