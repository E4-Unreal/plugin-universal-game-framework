// Fill out your copyright notice in the Description page of Project Settings.


#include "Input/UGFInputConfig.h"

#include "EnhancedInputComponent.h"

void UUGFInputConfig::BindEnhancedInput(UEnhancedInputComponent* EnhancedInputComponent)
{
    if (EnhancedInputComponent == nullptr) return;

    OnBindEnhancedInput(EnhancedInputComponent);
}

APlayerController* UUGFInputConfig::GetPlayerController(UEnhancedInputComponent* EnhancedInputComponent)
{
    if (EnhancedInputComponent)
    {
        if (AActor* Owner = EnhancedInputComponent->GetOwner())
        {
            if (APawn* OwnerPawn = Cast<APawn>(Owner))
            {
                return Cast<APlayerController>(OwnerPawn->GetController());
            }
        }
    }

    return nullptr;
}
