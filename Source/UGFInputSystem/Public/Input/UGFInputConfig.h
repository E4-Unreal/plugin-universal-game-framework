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
    TArray<uint32> BindEnhancedInput(UEnhancedInputComponent* EnhancedInputComponent);

protected:
    static APawn* GetOwningPlayerPawn(UEnhancedInputComponent* EnhancedInputComponent);
    static APlayerController* GetOwningPlayer(UEnhancedInputComponent* EnhancedInputComponent);

    virtual TArray<uint32> OnBindEnhancedInput(UEnhancedInputComponent* EnhancedInputComponent) { return TArray<uint32>(); }
};
