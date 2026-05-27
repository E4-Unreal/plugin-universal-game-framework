// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UGFPlayerController.h"
#include "UGFTopViewPlayerController.generated.h"

/**
 *
 */
UCLASS()
class UNIVERSALGAMEFRAMEWORK_API AUGFTopViewPlayerController : public AUGFPlayerController
{
    GENERATED_BODY()

public:
    AUGFTopViewPlayerController(const FObjectInitializer& ObjectInitializer);
};
