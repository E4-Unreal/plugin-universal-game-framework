// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InteractableActorBase.h"
#include "InteractableActor.generated.h"

UCLASS()
class INTERACTIONSYSTEM_API AInteractableActor : public AInteractableActorBase
{
    GENERATED_BODY()

protected:
    static FName DefaultSceneName;
    static FName DisplayMeshName;

private:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component", meta = (AllowPrivateAccess = "true"))
    TObjectPtr<USceneComponent> DefaultScene;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component", meta = (AllowPrivateAccess = "true"))
    TObjectPtr<UStaticMeshComponent> DisplayMesh;

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config", meta = (Categories = "Interaction"))
    FGameplayTag InteractionType;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
    FText InteractionText;

public:
    AInteractableActor(const FObjectInitializer& ObjectInitializer);

    /* InteractableInterface */

    virtual void SetFocus_Implementation(AActor* Interactor) override;
    virtual void ClearFocus_Implementation(AActor* Interactor) override;

    FORCEINLINE USceneComponent* GetDefaultScene() const { return DefaultScene; }
    FORCEINLINE UStaticMeshComponent* GetDisplayMesh() const { return DisplayMesh; }
};
