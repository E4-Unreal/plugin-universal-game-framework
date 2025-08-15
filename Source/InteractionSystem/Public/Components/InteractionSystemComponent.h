// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Components/SphereComponent.h"
#include "InteractionSystemComponent.generated.h"

class IInteractableInterface;

UCLASS(meta = (BlueprintSpawnableComponent))
class INTERACTIONSYSTEM_API UInteractionSystemComponent : public UActorComponent
{
    GENERATED_BODY()

protected:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Reference", Transient)
    TWeakObjectPtr<USphereComponent> OverlapSphere;

    UPROPERTY(VisibleAnywhere, Transient, Category = "State")
    TArray<TScriptInterface<IInteractableInterface>> AvailableTargets;

    UPROPERTY(VisibleAnywhere, Transient, Category = "State")
    TScriptInterface<IInteractableInterface> CurrentTarget;

public:
    UInteractionSystemComponent(const FObjectInitializer& ObjectInitializer);

    virtual void InitializeComponent() override;
    virtual void BeginPlay() override;
    virtual void OnComponentDestroyed(bool bDestroyingHierarchy) override;

    /* API */

    UFUNCTION(BlueprintCallable)
    virtual void SetOverlapSphere(USphereComponent* NewOverlapSphere);

    UFUNCTION(BlueprintCallable)
    virtual void AddTarget(const TScriptInterface<IInteractableInterface>& NewTarget);

    UFUNCTION(BlueprintCallable)
    virtual void RemoveTarget(const TScriptInterface<IInteractableInterface>& OldTarget);

    UFUNCTION(BlueprintCallable)
    virtual void TryInteract();

    UFUNCTION(BlueprintCallable)
    virtual void CancelInteract();

protected:
    UFUNCTION()
    virtual void OnOverlapSphereBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

    UFUNCTION()
    virtual void OnOverlapSphereEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

    virtual void RefreshTarget();

    float CalculateTargetDistance(const TScriptInterface<IInteractableInterface>& Target) const;
};
