// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Interfaces/CustomerInterface.h"
#include "UGFCharacter.generated.h"

class UCurrencyManagerComponent;
class UInventoryComponent;
class UInteractionSystemComponent;
class UInputBinderComponent;
class USpringArmComponent;
class UCameraComponent;

UCLASS()
class UNIVERSALGAMEFRAMEWORK_API AUGFCharacter : public ACharacter, public ICustomerInterface
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
    TObjectPtr<UInteractionSystemComponent> InteractionSystem;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component", meta = (AllowPrivateAccess = "true"))
    TObjectPtr<UCurrencyManagerComponent> CurrencyManager;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component", meta = (AllowPrivateAccess = "true"))
    TObjectPtr<UInventoryComponent> Inventory;

public:
    AUGFCharacter(const FObjectInitializer& ObjectInitializer);

    /* CustomerInterface */

    virtual int32 GetCurrency_Implementation(const FGameplayTag& CurrencyType) const override;
    virtual bool AddCurrency_Implementation(const FGameplayTag& CurrencyType, int32 Quantity) override;
    virtual bool RemoveCurrency_Implementation(const FGameplayTag& CurrencyType, int32 Quantity) override;
    virtual bool AddProduct_Implementation(const TScriptInterface<IProductInterface>& Product, int32 Quantity) override;
    virtual bool RemoveProduct_Implementation(const TScriptInterface<IProductInterface>& Product, int32 Quantity) override;

    /* Getter */

    FORCEINLINE USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
    FORCEINLINE UCameraComponent* GetFollowCamera() const { return FollowCamera; }
    FORCEINLINE UInputBinderComponent* GetInputBinder() const { return InputBinder; }
    FORCEINLINE UInteractionSystemComponent* GetInteractionSystem() const { return InteractionSystem; }
    FORCEINLINE UCurrencyManagerComponent* GetCurrencyManager() const { return CurrencyManager; }
    FORCEINLINE UInventoryComponent* GetInventory() const { return Inventory; }
};
