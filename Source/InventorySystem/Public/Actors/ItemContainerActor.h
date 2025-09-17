// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actors/InteractableActor.h"
#include "Interfaces/ItemActorInterface.h"
#include "ItemContainerActor.generated.h"

class UItemDropComponent;

UCLASS()
class INVENTORYSYSTEM_API AItemContainerActor : public AInteractableActor, public IItemActorInterface
{
    GENERATED_BODY()

protected:
    const static FName ItemContainerName;

private:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component", meta = (AllowPrivateAccess = "true"))
    TObjectPtr<UItemDropComponent> ItemContainer;

public:
    AItemContainerActor(const FObjectInitializer& ObjectInitializer);

    /* InteractableInterface */

    virtual void Interact_Implementation(AActor* Interactor) override;

    /* ItemActorInterface */

    virtual void SetItemInstances_Implementation(const TArray<UObject*>& NewItemsInstances) override;

public:
    /* Component */

    FORCEINLINE UItemDropComponent* GetItemContainer() const { return ItemContainer; }
};
