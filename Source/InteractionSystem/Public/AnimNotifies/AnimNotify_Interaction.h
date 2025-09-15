// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "GameplayTagContainer.h"
#include "AnimNotify_Interaction.generated.h"

/**
 * 상호작용 지속 가능 여부에 따라 애니메이션 중지 여부를 결정합니다.
 */
UCLASS(Const, hideCategories = Object, collapseCategories, Meta = (DisplayName = "Interaction"))
class INTERACTIONSYSTEM_API UAnimNotify_Interaction : public UAnimNotify
{
    GENERATED_BODY()

protected:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
    bool bLoop;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config", meta = (Categories = "Interaction"))
    FGameplayTag InteractionType;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
    FName LoopSectionName;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
    FName EndSectionName;

public:
    UAnimNotify_Interaction();

    /* AnimNotify */

    virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override;
};
