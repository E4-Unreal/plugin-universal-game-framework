// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnhancedInputSubsystemInterface.h"
#include "Components/ActorComponent.h"
#include "InputManagerComponent.generated.h"

class UInputMappingContext;
class UEnhancedInputLocalPlayerSubsystem;

UCLASS(meta = (BlueprintSpawnableComponent))
class INPUTMANAGER_API UInputManagerComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
    TArray<TObjectPtr<UInputMappingContext>> DefaultMappingContexts;

public:
    UInputManagerComponent();

    /* ActorComponent */

    virtual void BeginPlay() override;
    virtual void OnComponentDestroyed(bool bDestroyingHierarchy) override;

    /* ThisClass */

    UFUNCTION(BlueprintCallable)
    void AddMappingContext(const UInputMappingContext* MappingContext, int32 Priority = 0, const FModifyContextOptions& Options = FModifyContextOptions());

    UFUNCTION(BlueprintCallable)
    void AddMappingContexts(const TArray<UInputMappingContext*>& MappingContexts, int32 Priority = 0, const FModifyContextOptions& Options = FModifyContextOptions());

    UFUNCTION(BlueprintCallable)
    void RemoveMappingContext(const UInputMappingContext* MappingContext, const FModifyContextOptions& Options = FModifyContextOptions());

    UFUNCTION(BlueprintCallable)
    void RemoveMappingContexts(const TArray<UInputMappingContext*>& MappingContexts, const FModifyContextOptions& Options = FModifyContextOptions());

protected:
    /* ThisClass */

    UFUNCTION(BlueprintPure)
    UEnhancedInputLocalPlayerSubsystem* GetEnhancedInputLocalPlayerSubsystem() const;
};
