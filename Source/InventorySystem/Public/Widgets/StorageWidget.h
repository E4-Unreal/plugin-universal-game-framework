// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonUserWidget.h"
#include "StorageWidget.generated.h"

class UInventoryPanelWidget;

/**
 *
 */
UCLASS()
class INVENTORYSYSTEM_API UStorageWidget : public UCommonUserWidget
{
    GENERATED_BODY()

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component", meta = (AllowPrivateAccess = "true", BindWidget))
    TObjectPtr<UInventoryPanelWidget> StoragePanel;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component", meta = (AllowPrivateAccess = "true", BindWidget))
    TObjectPtr<UInventoryPanelWidget> InventoryPanel;

    UPROPERTY(VisibleAnywhere, BlueprintGetter = GetTargetActor, BlueprintSetter = SetTargetActor, Transient, meta = (AllowPrivateAccess = "true"))
    TObjectPtr<AActor> TargetActor;

public:
    UFUNCTION(BlueprintGetter)
    FORCEINLINE AActor* GetTargetActor() const { return TargetActor; }

    UFUNCTION(BlueprintSetter)
    void SetTargetActor(AActor* NewTargetActor);

protected:
    virtual void OnTargetActorChanged(AActor* OldTargetActor, AActor* NewTargetActor);

    FORCEINLINE UInventoryPanelWidget* GetStoragePanel() const { return StoragePanel; }
    FORCEINLINE UInventoryPanelWidget* GetInventoryPanel() const { return InventoryPanel; }
};
