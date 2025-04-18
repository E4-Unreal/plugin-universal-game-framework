// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonUserWidget.h"
#include "InventoryWidgetBase.generated.h"

class UInventoryComponent;

UCLASS(Abstract)
class INVENTORYSYSTEM_API UInventoryWidgetBase : public UCommonUserWidget
{
    GENERATED_BODY()

private:
    TWeakObjectPtr<UInventoryComponent> InventoryComponentPrivate;

public:
    UFUNCTION(BlueprintCallable)
    void SetInventoryComponent(UInventoryComponent* NewInventoryComponent);

    UFUNCTION(BlueprintCallable)
    virtual void Refresh() {}

protected:
    virtual void NativeOnInitialized() override;

    virtual void FindInventoryComponent();

    void FindInventoryComponentFromPlayer();

    void FindInventoryComponentFromPlayerPawn();

    virtual void OnInventoryComponentChanged(UInventoryComponent* OldInventoryComponent, UInventoryComponent* NewInventoryComponent) {}

    UFUNCTION(BlueprintPure)
    FORCEINLINE UInventoryComponent* GetInventoryComponent() const { return InventoryComponentPrivate.Get(); }
};
