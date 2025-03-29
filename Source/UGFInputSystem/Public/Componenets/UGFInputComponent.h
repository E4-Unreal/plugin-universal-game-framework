// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "UGFInputComponent.generated.h"

class UEnhancedInputComponent;
class UEnhancedInputLocalPlayerSubsystem;
class UInputMappingContext;
class UUGFInputConfig;

USTRUCT(Atomic, BlueprintType)
struct FUGFInputMappingContextData
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TObjectPtr<UInputMappingContext> InputMappingContext;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 Priority;
};

/**
 * PlayerController 및 Pawn 전용 입력 액션 컴포넌트
 */
UCLASS(meta = (BlueprintSpawnableComponent))
class UGFINPUTSYSTEM_API UUGFInputComponent : public UActorComponent
{
    GENERATED_BODY()

protected:
    UPROPERTY(EditDefaultsOnly, Category = "Config")
    TArray<FUGFInputMappingContextData> InputMappingContextDataList;

    UPROPERTY(EditDefaultsOnly, Category = "Config")
    TArray<TObjectPtr<UUGFInputConfig>> InputConfigs;

    UPROPERTY(VisibleInstanceOnly, Category = "State")
    TArray<uint32> InputBindingHandles;

public:
    UFUNCTION(BlueprintCallable)
    virtual void BindEnhancedInput();

    UFUNCTION(BlueprintCallable)
    virtual void UnBindEnhancedInput();

protected:
    UFUNCTION(BlueprintPure)
    FORCEINLINE bool IsPawn() const { return GetOwner()->GetClass()->IsChildOf(APawn::StaticClass()); }

    UFUNCTION(BlueprintPure)
    FORCEINLINE bool IsPlayerController() const { return GetOwner()->GetClass()->IsChildOf(APlayerController::StaticClass()); }

    UFUNCTION(BlueprintPure)
    APawn* GetOwningPawn() const;

    UFUNCTION(BlueprintPure)
    APlayerController* GetOwningPlayer() const;

    UFUNCTION(BlueprintPure)
    UEnhancedInputComponent* GetEnhancedInputComponent() const;

    UFUNCTION(BlueprintPure)
    UEnhancedInputLocalPlayerSubsystem* GetEnhancedInputLocalPlayerSubsystem() const;

    UFUNCTION(BlueprintCallable)
    virtual void BindInputConfigs();

    UFUNCTION(BlueprintCallable)
    virtual void UnBindInputConfigs();

    UFUNCTION(BlueprintCallable)
    virtual void AddMappingContexts();

    UFUNCTION(BlueprintCallable)
    virtual void RemoveMappingContexts();
};
