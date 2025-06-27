// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "UGFCharacter.generated.h"

class UCurrencyManagerComponent;
class UInventoryComponent;
class UInteractionSystemComponentBase;
class UInputBinderComponent;
class USpringArmComponent;
class UCameraComponent;

UCLASS()
class UNIVERSALGAMEFRAMEWORK_API AUGFCharacter : public ACharacter
{
    GENERATED_BODY()

protected:
    const static FName CameraBoomName;
    const static FName FollowCameraName;
    const static FName InputBinderName;
    const static FName InteractionSystemName;
    const static FName CurrencyManagerName;
    const static FName InventoryName;

private:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component", meta = (AllowPrivateAccess = "true"))
    TObjectPtr<USpringArmComponent> CameraBoom;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component", meta = (AllowPrivateAccess = "true"))
    TObjectPtr<UCameraComponent> FollowCamera;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component", meta = (AllowPrivateAccess = "true"))
    TObjectPtr<UInputBinderComponent> InputBinder;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component", meta = (AllowPrivateAccess = "true"))
    TObjectPtr<UInteractionSystemComponentBase> InteractionSystem;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component", meta = (AllowPrivateAccess = "true"))
    TObjectPtr<UCurrencyManagerComponent> CurrencyManager;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component", meta = (AllowPrivateAccess = "true"))
    TObjectPtr<UInventoryComponent> Inventory;

public:
    AUGFCharacter(const FObjectInitializer& ObjectInitializer);

public:
    FORCEINLINE USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
    FORCEINLINE UCameraComponent* GetFollowCamera() const { return FollowCamera; }
    FORCEINLINE UInputBinderComponent* GetInputBinder() const { return InputBinder; }
    FORCEINLINE UInteractionSystemComponentBase* GetInteractionSystem() const { return InteractionSystem; }
    FORCEINLINE UCurrencyManagerComponent* GetCurrencyManager() const { return CurrencyManager; }
    FORCEINLINE UInventoryComponent* GetInventory() const { return Inventory; }
};
