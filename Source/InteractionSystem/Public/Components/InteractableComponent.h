// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Components/ActorComponent.h"
#include "InteractableComponent.generated.h"

class UWidgetComponent;
class UShapeComponent;
class UInteractionSystemComponent;

UCLASS(meta = (BlueprintSpawnableComponent))
class INTERACTIONSYSTEM_API UInteractableComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config", meta = (MustImplement = "InteractionWidgetInterface"))
    TSubclassOf<UUserWidget> InteractionWidgetClass;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config", meta = (MustImplement = "TargetWidgetInterface"))
    TSubclassOf<UUserWidget> MenuWidgetClass;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config", meta = (Categories = "Interaction"))
    FGameplayTag InteractionType;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
    FText InteractionMessage;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
    bool bUseCursorEvent;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
    bool bUseOutlineEffect;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
    bool bUseOverlapShape;

protected:
    UPROPERTY(VisibleAnywhere, Category = "Reference", Transient)
    TWeakObjectPtr<UMeshComponent> DisplayMesh;

    UPROPERTY(VisibleAnywhere, Category = "Reference", Transient)
    TWeakObjectPtr<UWidgetComponent> WidgetComponent;

    UPROPERTY(VisibleAnywhere, Category = "Reference", Transient)
    TWeakObjectPtr<UShapeComponent> OverlapShape;

    UPROPERTY(VisibleAnywhere, Category = "State", Transient)
    TArray<TWeakObjectPtr<AActor>> OverlappingActors;

public:
    UInteractableComponent();

    /* ActorComponent */

    virtual void InitializeComponent() override;
    virtual void BeginPlay() override;
    virtual void OnComponentDestroyed(bool bDestroyingHierarchy) override;

    /* API */

    UFUNCTION(BlueprintCallable, Category = "Reference")
    virtual void SetDisplayMesh(UMeshComponent* NewDisplayMesh);

    UFUNCTION(BlueprintCallable, Category = "Reference")
    virtual void SetWidgetComponent(UWidgetComponent* NewWidgetComponent);

    UFUNCTION(BlueprintCallable, Category = "Reference")
    virtual void SetOverlapShape(UShapeComponent* NewOverlapShape);

    UFUNCTION(BlueprintPure)
    virtual bool CanInteract(AActor* Interactor) const;

    UFUNCTION(BlueprintCallable)
    void Interact(AActor* Interactor);

    UFUNCTION(BlueprintCallable)
    void CancelInteract(AActor* Interactor);

    UFUNCTION(BlueprintPure)
    virtual bool CanSelect(AActor* Interactor) const;

    UFUNCTION(BlueprintCallable)
    void Select(AActor* Interactor);

    UFUNCTION(BlueprintCallable)
    void Deselect(AActor* Interactor);

protected:
    /* Getter */

    TSubclassOf<UUserWidget> GetInteractionWidgetClass() const;
    UInteractionSystemComponent* GetPlayerInteractionSystem() const;

    /* API */

    UFUNCTION(BlueprintNativeEvent)
    void OnInteract(AActor* Interactor);

    UFUNCTION(BlueprintNativeEvent)
    void OnCancelInteract(AActor* Interactor);

    UFUNCTION(BlueprintNativeEvent)
    void OnSelect(AActor* Interactor);

    UFUNCTION(BlueprintNativeEvent)
    void OnDeselect(AActor* Interactor);

    virtual void ActivateOutlineEffect();
    virtual void DeactivateOutlineEffect();

    virtual void ShowInteractionWidget();
    virtual void HideInteractionWidget();

    virtual UUserWidget* ShowMenuWidget(AActor* PlayerActor);
    virtual bool HideMenuWidget(AActor* PlayerActor);

    virtual void FindDisplayMesh();
    virtual void FindWidgetComponent();
    virtual void FindOverlapShape();

    virtual void BindOverlapShapeEvents();
    virtual void UnbindOverlapShapeEvents();

    virtual void BindActorEvents();
    virtual void UnbindActorEvents();

    virtual void InitWidgetComponent() const;

    virtual void AddOverlappingActor(AActor* NewActor);
    virtual void RemoveOverlappingActor(AActor* OldActor);

    UFUNCTION()
    virtual void OnOverlapShapeBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

    UFUNCTION()
    virtual void OnOverlapShapeEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

    UFUNCTION()
    virtual void OnBeginCursorOver(AActor* TouchedActor);

    UFUNCTION()
    virtual void OnEndCursorOver(AActor* TouchedActor);

    UFUNCTION()
    virtual void OnClicked(AActor* TouchedActor, FKey ButtonPressed);
};
