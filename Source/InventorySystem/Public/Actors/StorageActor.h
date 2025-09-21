// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actors/InteractableActor.h"
#include "GameFramework/Actor.h"
#include "StorageActor.generated.h"

class UInventoryComponent;

UCLASS()
class INVENTORYSYSTEM_API AStorageActor : public AInteractableActor
{
    GENERATED_BODY()

protected:
    const static FName InventoryName;

private:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component", meta = (AllowPrivateAccess = "true"))
    TObjectPtr<UInventoryComponent> Inventory;

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
    TSubclassOf<UUserWidget> StorageWidgetClass;

public:
    AStorageActor(const FObjectInitializer& ObjectInitializer);

    /* InteractableInterface */

    virtual void Interact_Implementation(AActor* Interactor) override;

    /* Components */

    FORCEINLINE UInventoryComponent* GetInventory() const { return Inventory; }
};
