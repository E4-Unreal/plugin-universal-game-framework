// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actors/InteractableActor.h"
#include "Interfaces/ItemActorInterface.h"
#include "ItemActor.generated.h"

class UItemActorComponent;

UCLASS()
class INVENTORYSYSTEM_API AItemActor : public AInteractableActor, public IItemActorInterface
{
    GENERATED_BODY()

protected:
    const static FName ItemComponentName;

private:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component", meta = (AllowPrivateAccess = "true"))
    TObjectPtr<UItemActorComponent> ItemComponent;

public:
    AItemActor(const FObjectInitializer& ObjectInitializer);

    /* InteractableInterface */

    virtual FText GetInteractionMessage_Implementation() const override;
    virtual void Interact_Implementation(AActor* Interactor) override;

    /* ItemActorInterface */

    virtual void SetItemInstances_Implementation(const TArray<UDataInstanceBase*>& NewItemsInstances) override;

public:
    /* Component */

    FORCEINLINE UItemActorComponent* GetItemComponent() const { return ItemComponent; }
};
