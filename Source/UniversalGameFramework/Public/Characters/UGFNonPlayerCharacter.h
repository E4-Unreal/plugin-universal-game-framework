// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/InteractableCharacter.h"
#include "UGFNonPlayerCharacter.generated.h"

class UCommonLayerWidgetBase;

UCLASS()
class UNIVERSALGAMEFRAMEWORK_API AUGFNonPlayerCharacter : public AInteractableCharacter
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
    TSubclassOf<UCommonLayerWidgetBase> MenuWidgetClass;

public:
    AUGFNonPlayerCharacter(const FObjectInitializer& ObjectInitializer);

    /* InteractableInterface */

    virtual bool CanInteract_Implementation(AActor* Interactor) override;
    virtual void Interact_Implementation(AActor* Interactor) override;
    virtual void CancelInteract_Implementation(AActor* Interactor) override;
};
