// Fill out your copyright notice in the Description page of Project Settings.


#include "Input/UGFInputConfig.h"

#include "EnhancedInputComponent.h"

void UUGFInputConfig::BindEnhancedInput(UEnhancedInputComponent* EnhancedInputComponent)
{
    if (EnhancedInputComponent == nullptr) return;

    OnBindEnhancedInput(EnhancedInputComponent);
}

void UUGFInputConfig::UnBindEnhancedInput(UEnhancedInputComponent* EnhancedInputComponent)
{
    if (EnhancedInputComponent == nullptr) return;

    OnUnBindEnhancedInput(EnhancedInputComponent);
}

APawn* UUGFInputConfig::GetOwningPlayerPawn(UEnhancedInputComponent* EnhancedInputComponent)
{
    if (EnhancedInputComponent)
    {
        if (AActor* OwningActor = EnhancedInputComponent->GetOwner())
        {
            if (APawn* OwningPawn = Cast<APawn>(OwningActor))
            {
                return OwningPawn;
            }
        }
    }

    return nullptr;
}

APlayerController* UUGFInputConfig::GetOwningPlayer(UEnhancedInputComponent* EnhancedInputComponent)
{
    if (APawn* OwningPawn = GetOwningPlayerPawn(EnhancedInputComponent))
    {
        return Cast<APlayerController>(OwningPawn->GetController());
    }

    return nullptr;
}
