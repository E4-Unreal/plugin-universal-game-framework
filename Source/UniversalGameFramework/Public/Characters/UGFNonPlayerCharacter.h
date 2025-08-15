// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UGFCharacter.h"
#include "UGFNonPlayerCharacter.generated.h"

UCLASS()
class UNIVERSALGAMEFRAMEWORK_API AUGFNonPlayerCharacter : public AUGFCharacter
{
    GENERATED_BODY()

public:
    AUGFNonPlayerCharacter(const FObjectInitializer& ObjectInitializer);
};
