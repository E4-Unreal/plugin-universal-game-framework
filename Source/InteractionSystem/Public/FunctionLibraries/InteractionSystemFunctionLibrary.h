// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "InteractionSystemFunctionLibrary.generated.h"

struct FGameplayTag;

/**
 *
 */
UCLASS()
class INTERACTIONSYSTEM_API UInteractionSystemFunctionLibrary : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintPure)
    static UObject* GetInteractableObject(AActor* TargetActor);

    UFUNCTION(BlueprintPure)
    static FGameplayTag GetInteractionType(AActor* TargetActor);

    UFUNCTION(BlueprintPure)
    static FText GetInteractionMessage(AActor* TargetActor);

    UFUNCTION(BlueprintPure)
    static bool CanInteract(AActor* TargetActor, AActor* Interactor);

    UFUNCTION(BlueprintCallable)
    static void Interact(AActor* TargetActor, AActor* Interactor);

    UFUNCTION(BlueprintCallable)
    static void CancelInteract(AActor* TargetActor, AActor* Interactor);

    UFUNCTION(BlueprintPure)
    static bool CanSelect(AActor* TargetActor, AActor* Interactor);

    UFUNCTION(BlueprintCallable)
    static void Select(AActor* TargetActor, AActor* Interactor);

    UFUNCTION(BlueprintCallable)
    static void Deselect(AActor* TargetActor, AActor* Interactor);
};
