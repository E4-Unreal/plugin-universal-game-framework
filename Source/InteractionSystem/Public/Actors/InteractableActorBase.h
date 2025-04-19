// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interfaces/InteractableInterface.h"
#include "InteractableActorBase.generated.h"

class UInteractionSystemComponentBase;

UCLASS(Abstract)
class INTERACTIONSYSTEM_API AInteractableActorBase : public AActor, public IInteractableInterface
{
    GENERATED_BODY()

protected:
    static FName DisplayMeshName;
    static FName OverlapShapeName;

private:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component", meta = (AllowPrivateAccess = "true"))
    TObjectPtr<UMeshComponent> DisplayMesh;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component", meta = (AllowPrivateAccess = "true"))
    TObjectPtr<UShapeComponent> OverlapShape;

public:
    AInteractableActorBase(const FObjectInitializer& ObjectInitializer);

    virtual void BeginPlay() override;

    UFUNCTION(BlueprintPure)
    virtual bool CanInteract() const { return !IsHidden(); }

protected:
    UFUNCTION()
    virtual void OnOverlapShapeBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

    UFUNCTION()
    virtual void OnOverlapShapeEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

    UFUNCTION(BlueprintNativeEvent)
    void OnInteractorBeginOverlap(AActor* Interactor, UInteractionSystemComponentBase* InteractionSystem);

    UFUNCTION(BlueprintNativeEvent)
    void OnInteractorEndOverlap(AActor* Interactor,UInteractionSystemComponentBase* InteractionSystem);

public:
    FORCEINLINE UMeshComponent* GetDisplayMesh() const { return DisplayMesh.Get(); }

    template<typename T = UMeshComponent>
    T* GetDisplayMesh() const { return Cast<T>(GetDisplayMesh()); }

    FORCEINLINE UShapeComponent* GetOverlapShape() const { return OverlapShape.Get(); }

    template<typename T = UShapeComponent>
    T* GetOverlapShape() const { return Cast<T>(GetOverlapShape()); }
};
