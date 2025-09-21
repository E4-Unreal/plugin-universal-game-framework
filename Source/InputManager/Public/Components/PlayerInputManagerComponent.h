// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PlayerInputManagerComponent.generated.h"

class UInputMappingContext;
class UEnhancedInputLocalPlayerSubsystem;

UCLASS(meta = (BlueprintSpawnableComponent))
class INPUTMANAGER_API UPlayerInputManagerComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
    TArray<TObjectPtr<UInputMappingContext>> DefaultMappingContexts;

public:
    UPlayerInputManagerComponent();

    /* ActorComponent */

    virtual void BeginPlay() override;
    virtual void OnComponentDestroyed(bool bDestroyingHierarchy) override;

protected:
    /* API */

    UEnhancedInputLocalPlayerSubsystem* GetEnhancedInputLocalPlayerSubsystem() const;

    virtual void AddDefaultMappingContexts();
    virtual void RemoveDefaultMappingContexts();
};
