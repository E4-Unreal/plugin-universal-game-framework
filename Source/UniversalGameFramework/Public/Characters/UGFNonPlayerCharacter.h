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
    AUGFNonPlayerCharacter(const FObjectInitializer& ObjectInitializer);
};
