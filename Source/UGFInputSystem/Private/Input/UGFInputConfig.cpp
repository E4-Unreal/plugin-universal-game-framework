// Fill out your copyright notice in the Description page of Project Settings.


#include "Input/UGFInputConfig.h"

void UUGFInputConfig::BindEnhancedInput(UEnhancedInputComponent* EnhancedInputComponent)
{
    if (EnhancedInputComponent == nullptr) return;

    OnBindEnhancedInput(EnhancedInputComponent);
}
