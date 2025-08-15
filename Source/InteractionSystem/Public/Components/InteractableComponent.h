// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Interfaces/InteractableInterface.h"
#include "InteractableComponent.generated.h"

class UInteractableComponent;
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FInteractionTriggeredSignature, AActor*, Interactor);

class UInteractionSystemComponentBase;

UCLASS(meta = (BlueprintSpawnableComponent))
class INTERACTIONSYSTEM_API UInteractableComponent : public UActorComponent, public IInteractableInterface
{
    GENERATED_BODY()

    TWeakObjectPtr<UShapeComponent> OverlapShape;

public:
    UPROPERTY(BlueprintAssignable)
    FInteractionTriggeredSignature OnInteractionTriggered;

protected:
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Config")
    bool bCanInteractOnlyOnce = true;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Config")
    float InteractionTime = -1.0f;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State", Transient)
    bool bCanInteract = true;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State", Transient)
    TMap<TObjectPtr<AActor>, FTimerHandle> InteractionTimerMap;

public:
    /* InteractableInterface */

    virtual bool CanInteract_Implementation(AActor* Interactor) override { return bCanInteract && Interactor && !GetOwner()->IsHidden() && !IsInteracting(Interactor); }
    virtual void Interact_Implementation(AActor* Interactor) override;
    virtual void CancelInteract_Implementation(AActor* Interactor) override;

    /* ActorComponent */

    virtual void BeginPlay() override;
    virtual void OnComponentDestroyed(bool bDestroyingHierarchy) override;

    /* InteractableComponent */

    UFUNCTION(BlueprintPure, Category = "Reference")
    FORCEINLINE UShapeComponent* GetOverlapShape() const { return OverlapShape.Get(); }

    UFUNCTION(BlueprintCallable, Category = "Reference")
    void SetOverlapShape(UShapeComponent* NewOverlapShape) { if (OverlapShape != NewOverlapShape) OverlapShape = NewOverlapShape; }

protected:
    virtual void SetInteractionTimer(AActor* Interactor);
    virtual void ClearInteractionTimer(AActor* Interactor);
    virtual void ClearAllInteractionTimers();
    virtual void TriggerInteraction(AActor* Interactor);

    virtual bool IsInteracting(AActor* Interactor) { return Interactor && InteractionTimerMap.Contains(Interactor); }

    UFUNCTION()
    virtual void OnOverlapShapeBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

    UFUNCTION()
    virtual void OnOverlapShapeEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

    UFUNCTION(BlueprintNativeEvent)
    void OnInteractorBeginOverlap(AActor* Interactor, UInteractionSystemComponentBase* InteractionSystem);

    UFUNCTION(BlueprintNativeEvent)
    void OnInteractorEndOverlap(AActor* Interactor,UInteractionSystemComponentBase* InteractionSystem);
};
