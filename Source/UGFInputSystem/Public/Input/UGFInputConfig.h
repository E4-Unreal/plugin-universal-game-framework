// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "UGFInputConfig.generated.h"

/**
 * 입력 바인딩 전용 데이터 에셋
 */
UCLASS(Abstract)
class UGFINPUTSYSTEM_API UUGFInputConfig : public UPrimaryDataAsset
{
    GENERATED_BODY()

public:
    void BindEnhancedInput(UEnhancedInputComponent* EnhancedInputComponent);
    void UnBindEnhancedInput(UEnhancedInputComponent* EnhancedInputComponent);

protected:
    static APlayerController* GetPlayerController(UEnhancedInputComponent* EnhancedInputComponent);

    virtual void OnBindEnhancedInput(UEnhancedInputComponent* EnhancedInputComponent) { }
    virtual void OnUnBindEnhancedInput(UEnhancedInputComponent* EnhancedInputComponent) { }
};
