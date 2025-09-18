// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actors/InteractableActor.h"
#include "ItemDropActor.generated.h"

class UItemDropComponent;

UCLASS()
class INVENTORYSYSTEM_API AItemDropActor : public AInteractableActor
{
    GENERATED_BODY()

protected:
    const static FName ItemDropComponentName;

private:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component", meta = (AllowPrivateAccess = "true"))
    TObjectPtr<UItemDropComponent> ItemDropComponent;

public:
    AItemDropActor(const FObjectInitializer& ObjectInitializer);

    /* InteractableInterface */

    virtual void Interact_Implementation(AActor* Interactor) override;

public:
    /* Component */

    FORCEINLINE UItemDropComponent* GetItemDropContainer() const { return ItemDropComponent; }
};
