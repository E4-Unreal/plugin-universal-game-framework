// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actors/InteractableActor.h"
#include "Interfaces/ItemActorInterface.h"
#include "Types/ItemInstance.h"
#include "ItemActor.generated.h"

struct FInventoryItemData;

UCLASS()
class INVENTORYSYSTEM_API AItemActor : public AInteractableActor, public IItemActorInterface
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config", meta = (ShowOnlyInnerProperties))
    TArray<FItemInstance> InventoryItems;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
    TObjectPtr<UStaticMesh> DefaultStaticMesh;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
    bool bAutoDestroy = true;

public:
    AItemActor(const FObjectInitializer& ObjectInitializer);

    /* IItemActorInterface */

    virtual void SetInventoryItems_Implementation(const TArray<FItemInstance>& NewInventoryItems) override;

    /* Actor */

    virtual void PostInitializeComponents() override;
    virtual void BeginPlay() override;
#if WITH_EDITOR
    virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
#endif

protected:
    /* InteractableActor */

    virtual void OnInteractionTriggered_Implementation(AActor* Interactor) override;

    /* ItemActor */

    UFUNCTION(BlueprintCallable)
    virtual void Refresh();

    UFUNCTION(BlueprintPure)
    virtual UStaticMesh* GetStaticMesh() const;
};
