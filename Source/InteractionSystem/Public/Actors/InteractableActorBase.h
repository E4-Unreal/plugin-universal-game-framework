// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interfaces/InteractableInterface.h"
#include "InteractableActorBase.generated.h"

class UInteractableComponent;

UCLASS(Abstract)
class INTERACTIONSYSTEM_API AInteractableActorBase : public AActor, public IInteractableInterface
{
    GENERATED_BODY()

protected:
    static FName DisplayMeshName;
    static FName OverlapShapeName;
    static FName InteractableComponentName;

private:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component", meta = (AllowPrivateAccess = "true"))
    TObjectPtr<UMeshComponent> DisplayMesh;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component", meta = (AllowPrivateAccess = "true"))
    TObjectPtr<UShapeComponent> OverlapShape;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component", meta = (AllowPrivateAccess = "true"))
    TObjectPtr<UInteractableComponent> InteractableComponent;

public:
    AInteractableActorBase(const FObjectInitializer& ObjectInitializer);

    virtual void BeginPlay() override;

    /* InteractableInterface */

    virtual bool CanInteract_Implementation(AActor* Interactor) override;
    virtual void Interact_Implementation(AActor* Interactor) override;
    virtual void CancelInteract_Implementation(AActor* Interactor) override;

protected:
    UFUNCTION(BlueprintNativeEvent)
    void OnInteractionTriggered(AActor* Interactor);

public:
    FORCEINLINE UMeshComponent* GetDisplayMesh() const { return DisplayMesh.Get(); }
    FORCEINLINE UShapeComponent* GetOverlapShape() const { return OverlapShape.Get(); }
    FORCEINLINE UInteractableComponent* GetInteractableComponent() const { return InteractableComponent.Get(); }
};
