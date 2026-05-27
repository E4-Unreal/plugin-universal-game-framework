// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnhancedInputSubsystemInterface.h"
#include "Components/ActorComponent.h"
#include "InputManagerComponent.generated.h"

class UInputMappingContext;
class UEnhancedInputLocalPlayerSubsystem;
struct FInputActionConfigData;

UCLASS(meta = (BlueprintSpawnableComponent))
class INPUTMANAGER_API UInputManagerComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
    TArray<TObjectPtr<UInputMappingContext>> DefaultMappingContexts;

    UPROPERTY(VisibleAnywhere, Category = "State", Transient)
    TArray<uint32> InputActionBindingHandles;

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

    UFUNCTION(BlueprintCallable)
    void BindInputAction(const FInputActionConfigData& Config);

    UFUNCTION(BlueprintCallable)
    void UnbindInputAction(const FInputActionConfigData& Config);

protected:
    /* ThisClass */

    UFUNCTION(BlueprintPure)
    APlayerController* GetPlayerController() const;

    UFUNCTION(BlueprintPure)
    UEnhancedInputLocalPlayerSubsystem* GetEnhancedInputLocalPlayerSubsystem() const;

    UFUNCTION(BlueprintPure)
    UEnhancedInputComponent* GetEnhancedInputComponent() const;

    UFUNCTION(BlueprintPure)
    virtual TArray<FInputActionConfigData> GetInputActionConfigs() const { return TArray<FInputActionConfigData>(); }

    UFUNCTION(BlueprintCallable)
    virtual void BindInputActions();

    UFUNCTION(BlueprintCallable)
    virtual void UnbindInputActions();

    UFUNCTION(BlueprintNativeEvent)
    void OnInputActionTriggered(const FInputActionInstance& InputActionInstance);

    UFUNCTION(BlueprintNativeEvent)
    void OnInputActionStarted(const FInputActionInstance& InputActionInstance);

    UFUNCTION(BlueprintNativeEvent)
    void OnInputActionOngoing(const FInputActionInstance& InputActionInstance);

    UFUNCTION(BlueprintNativeEvent)
    void OnInputActionCanceled(const FInputActionInstance& InputActionInstance);

    UFUNCTION(BlueprintNativeEvent)
    void OnInputActionCompleted(const FInputActionInstance& InputActionInstance);
};
