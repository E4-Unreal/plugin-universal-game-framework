// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Types/InputActionConfigData.h"
#include "PawnInputManagerComponentBase.generated.h"

struct FInputActionInstance;

/**
 * Pawn 클래스에 부착되며 향상된 입력 액션 바인딩을 위한 컴포넌트로 필요에 따라 상속받아 사용
 */
UCLASS(Abstract, Blueprintable, meta = (BlueprintSpawnableComponent))
class INPUTMANAGER_API UPawnInputManagerComponentBase : public UActorComponent
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
    TArray<FInputActionConfigData> InputActionConfigs;

protected:
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Reference", Transient)
    TWeakObjectPtr<UEnhancedInputComponent> EnhancedInputComponent;

    UPROPERTY(VisibleAnywhere, Category = "State", Transient)
    TArray<uint32> InputActionBindingHandles;

public:
    UPawnInputManagerComponentBase();

    /* ActorComponent */

    virtual void BeginPlay() override;
    virtual void OnComponentDestroyed(bool bDestroyingHierarchy) override;

protected:
    /* API */

    virtual void BindInputActions();
    virtual void UnBindInputActions();

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

    virtual void BindPawnRestartedEvent();
    virtual void UnBindPawnRestartedEvent();

    UFUNCTION()
    virtual void OnOwningPawnRestarted(APawn* OwningPawn);
};
