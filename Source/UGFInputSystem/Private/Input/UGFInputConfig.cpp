// Fill out your copyright notice in the Description page of Project Settings.


#include "Input/UGFInputConfig.h"

#include "EnhancedInputComponent.h"

TArray<uint32> UUGFInputConfig::BindEnhancedInput(UEnhancedInputComponent* EnhancedInputComponent)
{
    return EnhancedInputComponent != nullptr ? OnBindEnhancedInput(EnhancedInputComponent) : TArray<uint32>();
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
