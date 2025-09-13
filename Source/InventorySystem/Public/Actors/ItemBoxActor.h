// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actors/InteractableActor.h"
#include "GameFramework/Actor.h"
#include "ItemBoxActor.generated.h"

class UDataInstanceBase;

UCLASS()
class INVENTORYSYSTEM_API AItemBoxActor : public AInteractableActor
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config", meta = (MustImplement = "ItemActorInterface"))
    TSubclassOf<AActor> ItemActorClass;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config", meta = (MustImplement = "ItemInstanceInterface"), Instanced)
    TArray<TObjectPtr<UDataInstanceBase>> ItemInstances;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
    FVector SpawnOffset;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config", meta = (ClampMin = 0, ClampMax = 90))
    float ImpulseAngle;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config", meta = (ClampMin = 0))
    float ImpulseStrength;

public:
    AItemBoxActor(const FObjectInitializer& ObjectInitializer);

    /* InteractableInterface */

    virtual void Interact_Implementation(AActor* Interactor) override;

    /* API */

    UFUNCTION(BlueprintCallable)
    virtual AActor* SpawnItem(UDataInstanceBase* InItemInstance);
};
