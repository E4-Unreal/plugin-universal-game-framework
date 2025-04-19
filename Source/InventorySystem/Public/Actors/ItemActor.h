// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actors/InteractableActor.h"
#include "Types/InventoryItem.h"
#include "ItemActor.generated.h"

struct FInventoryItemData;

UCLASS()
class INVENTORYSYSTEM_API AItemActor : public AInteractableActor
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config", meta = (ShowOnlyInnerProperties))
    TArray<FInventoryItem> InventoryItemList;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
    TObjectPtr<UStaticMesh> DefaultStaticMesh;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
    bool bAutoDestroy = true;

public:
    AItemActor(const FObjectInitializer& ObjectInitializer);

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
