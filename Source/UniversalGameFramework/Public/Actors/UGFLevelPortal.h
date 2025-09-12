// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actors/InteractableActor.h"
#include "UGFLevelPortal.generated.h"

UCLASS()
class UNIVERSALGAMEFRAMEWORK_API AUGFLevelPortal : public AInteractableActor
{
    GENERATED_BODY()

protected:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
    FText LevelName;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
    TSoftObjectPtr<UWorld> Level;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
    FText ConfirmTitle;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
    FText ConfirmMessage;

public:
    AUGFLevelPortal(const FObjectInitializer& ObjectInitializer);

    /* InteractableInterface */

    virtual FText GetInteractionMessage_Implementation() const override;
    virtual void Interact_Implementation(AActor* Interactor) override;

protected:
    virtual void RequestConfirmPopup(APlayerController* PlayerController);

    UFUNCTION()
    virtual void MoveToLevel();
};
