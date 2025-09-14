// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Components/SphereComponent.h"
#include "InteractionSystemComponent.generated.h"

class UCapsuleComponent;

UCLASS(meta = (BlueprintSpawnableComponent))
class INTERACTIONSYSTEM_API UInteractionSystemComponent : public UActorComponent
{
    GENERATED_BODY()

protected:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
    float Range;

protected:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Reference", Transient)
    TWeakObjectPtr<USphereComponent> OverlapSphere;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Reference", Transient)
    TWeakObjectPtr<UCapsuleComponent> OverlapCapsule;

    UPROPERTY(VisibleAnywhere, Category = "State", Transient)
    TArray<TWeakObjectPtr<AActor>> AvailableTargets;

    UPROPERTY(VisibleAnywhere, Category = "State", Transient)
    TArray<TWeakObjectPtr<AActor>> SelectedTargets;

public:
    UInteractionSystemComponent(const FObjectInitializer& ObjectInitializer);

    /* ActorComponent */

    virtual void InitializeComponent() override;
    virtual void BeginPlay() override;
    virtual void OnComponentDestroyed(bool bDestroyingHierarchy) override;

    /* API */

    UFUNCTION(BlueprintPure)
    TArray<AActor*> GetSelectedTargets();

    UFUNCTION(BlueprintCallable)
    virtual void SetOverlapSphere(USphereComponent* NewOverlapSphere);

    UFUNCTION(BlueprintCallable)
    virtual void SetOverlapCapsule(UCapsuleComponent* NewOverlapCapsule);

    UFUNCTION(BlueprintPure)
    FORCEINLINE float GetRange() const { return Range; }

    UFUNCTION(BlueprintCallable)
    virtual void SetRange(float NewRange);

    UFUNCTION(BlueprintCallable)
    virtual void AddTarget(AActor* NewTarget);

    UFUNCTION(BlueprintCallable)
    virtual void RemoveTarget(AActor* OldTarget);

    UFUNCTION(BlueprintCallable)
    virtual void SelectTarget(AActor* NewTarget, bool bForce = false);

    UFUNCTION(BlueprintCallable)
    virtual void DeselectTarget(AActor* OldTarget, bool bForce = false);

    UFUNCTION(BlueprintCallable)
    virtual void RefreshTargets();

    UFUNCTION(BlueprintCallable)
    virtual bool TryInteract();

    UFUNCTION(BlueprintCallable)
    virtual void CancelInteract();

protected:
    /* API */

    static void ShrinkTargets(TArray<TWeakObjectPtr<AActor>>& InTargets);
    virtual void ShrinkAllTargets();

    virtual void FindOverlapSphere();
    virtual void FindOverlapCapsule();

    virtual void BindOverlapSphereEvents();
    virtual void UnBindOverlapSphereEvents();

    virtual void BindOverlapCapsuleEvents();
    virtual void UnBindOverlapCapsuleEvents();

    UFUNCTION()
    virtual void OnOverlapSphereBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

    UFUNCTION()
    virtual void OnOverlapSphereEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

    UFUNCTION()
    virtual void OnOverlapCapsuleBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

    UFUNCTION()
    virtual void OnOverlapCapsuleEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

    float GetDistanceToTarget(AActor* Target) const;
};
