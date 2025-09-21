// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UGFCharacter.h"
#include "Interfaces/CustomerInterface.h"
#include "UGFPlayerCharacter.generated.h"

class USaveGame;
class UEquipmentManagerComponent;
class UCurrencyManagerComponent;
class UInventoryComponent;
class UInteractionSystemComponent;
class UInputBinderComponent;
class USphereComponent;
class USpringArmComponent;
class UCameraComponent;
class UPawnWidgetManagerComponent;
class UWeaponManagerComponent;

UCLASS()
class UNIVERSALGAMEFRAMEWORK_API AUGFPlayerCharacter : public AUGFCharacter,
    public ICustomerInterface
{
    GENERATED_BODY()

protected:
    const static FName CameraBoomName;
    const static FName FollowCameraName;
    const static FName OverlapSphereName;
    const static FName InputBinderName;
    const static FName InteractionSystemName;
    const static FName CurrencyManagerName;
    const static FName InventoryName;
    const static FName EquipmentManagerName;
    const static FName PawnWidgetManagerName;
    const static FName WeaponManagerName;

private:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component", meta = (AllowPrivateAccess = "true"))
    TObjectPtr<USpringArmComponent> CameraBoom;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component", meta = (AllowPrivateAccess = "true"))
    TObjectPtr<UCameraComponent> FollowCamera;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component", meta = (AllowPrivateAccess = "true"))
    TObjectPtr<USphereComponent> OverlapSphere;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component", meta = (AllowPrivateAccess = "true"))
    TObjectPtr<UInputBinderComponent> InputBinder;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component", meta = (AllowPrivateAccess = "true"))
    TObjectPtr<UInteractionSystemComponent> InteractionSystem;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component", meta = (AllowPrivateAccess = "true"))
    TObjectPtr<UInventoryComponent> Inventory;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component", meta = (AllowPrivateAccess = "true"))
    TObjectPtr<UCurrencyManagerComponent> CurrencyManager;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component", meta = (AllowPrivateAccess = "true"))
    TObjectPtr<UEquipmentManagerComponent> EquipmentManager;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component", meta = (AllowPrivateAccess = "true"))
    TObjectPtr<UPawnWidgetManagerComponent> PawnWidgetManager;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component", meta = (AllowPrivateAccess = "true"))
    TObjectPtr<UWeaponManagerComponent> WeaponManager;

public:
    AUGFPlayerCharacter(const FObjectInitializer& ObjectInitializer);

    virtual void BeginPlay() override;

    /* CustomerInterface */

    virtual int32 GetCurrency_Implementation(const FGameplayTag& CurrencyType) const override;
    virtual bool AddCurrency_Implementation(const FGameplayTag& CurrencyType, int32 Quantity) override;
    virtual bool RemoveCurrency_Implementation(const FGameplayTag& CurrencyType, int32 Quantity) override;
    virtual bool AddProduct_Implementation(const TScriptInterface<IProductInterface>& Product, int32 Quantity) override;
    virtual bool RemoveProduct_Implementation(const TScriptInterface<IProductInterface>& Product, int32 Quantity) override;

    /* Getter */

    FORCEINLINE USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
    FORCEINLINE UCameraComponent* GetFollowCamera() const { return FollowCamera; }
    FORCEINLINE USphereComponent* GetOverlapSphere() const { return OverlapSphere; }
    FORCEINLINE UInputBinderComponent* GetInputBinder() const { return InputBinder; }
    FORCEINLINE UInteractionSystemComponent* GetInteractionSystem() const { return InteractionSystem; }
    FORCEINLINE UInventoryComponent* GetInventory() const { return Inventory; }
    FORCEINLINE UCurrencyManagerComponent* GetCurrencyManager() const { return CurrencyManager; }
    FORCEINLINE UEquipmentManagerComponent* GetEquipmentManager() const { return EquipmentManager; }
    FORCEINLINE UPawnWidgetManagerComponent* GetPawnWidgetManager() const { return PawnWidgetManager; }
    FORCEINLINE UWeaponManagerComponent* GetWeaponManager() const { return WeaponManager; }

protected:
    UFUNCTION(BlueprintNativeEvent)
    void OnSaveData(USaveGame* SaveGame);

    UFUNCTION(BlueprintNativeEvent)
    void OnLoadData(USaveGame* SaveGame);
};
