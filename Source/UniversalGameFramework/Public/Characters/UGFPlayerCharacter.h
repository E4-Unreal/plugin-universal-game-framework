// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UGFCharacter.h"
#include "UGFPlayerCharacter.generated.h"

UCLASS()
class UNIVERSALGAMEFRAMEWORK_API AUGFPlayerCharacter : public AUGFCharacter
{
    GENERATED_BODY()

public:
    AUGFPlayerCharacter(const FObjectInitializer& ObjectInitializer);
};
