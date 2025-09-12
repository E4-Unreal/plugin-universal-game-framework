// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InteractableActorBase.h"
#include "InteractableActor.generated.h"

class UWidgetComponent;
class UInteractionSystemComponent;

UCLASS()
class INTERACTIONSYSTEM_API AInteractableActor : public AInteractableActorBase
{
    GENERATED_BODY()

protected:
    static FName DefaultSceneName;
    static FName DisplayMeshName;
    static FName WidgetComponentName;

private:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component", meta = (AllowPrivateAccess = "true"))
    TObjectPtr<USceneComponent> DefaultScene;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component", meta = (AllowPrivateAccess = "true"))
    TObjectPtr<UStaticMeshComponent> DisplayMesh;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component", meta = (AllowPrivateAccess = "true"))
    TObjectPtr<UWidgetComponent> WidgetComponent;

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
    bool bUseCursorEvent;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
    bool bUseRenderCustomDepth;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config", meta = (Categories = "Interaction"))
    FGameplayTag InteractionType;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
    FText InteractionMessage;

public:
    AInteractableActor(const FObjectInitializer& ObjectInitializer);

    /* Actor */

    virtual void BeginPlay() override;
    virtual void NotifyActorBeginCursorOver() override;
    virtual void NotifyActorEndCursorOver() override;
    virtual void NotifyActorOnClicked(FKey ButtonPressed) override;

    /* InteractableInterface */

    virtual FGameplayTag GetInteractionType_Implementation() const override { return InteractionType; }
    virtual FText GetInteractionMessage_Implementation() const override { return InteractionMessage; }
    virtual void SetFocus_Implementation(AActor* Interactor) override;
    virtual void ClearFocus_Implementation(AActor* Interactor) override;

public:
    FORCEINLINE USceneComponent* GetDefaultScene() const { return DefaultScene; }
    FORCEINLINE UStaticMeshComponent* GetDisplayMesh() const { return DisplayMesh; }
    FORCEINLINE UWidgetComponent* GetWidgetComponent() const { return WidgetComponent; }

protected:
    virtual UInteractionSystemComponent* GetPlayerInteractionSystem() const;
};
