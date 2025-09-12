// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InteractableActorBase.h"
#include "InteractableActor.generated.h"

class UWidgetComponent;
class USphereComponent;

UCLASS()
class INTERACTIONSYSTEM_API AInteractableActor : public AInteractableActorBase
{
    GENERATED_BODY()

protected:
    static FName DefaultSceneName;
    static FName DisplayMeshName;
    static FName WidgetComponentName;
    static FName OverlapSphereName;

private:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component", meta = (AllowPrivateAccess = "true"))
    TObjectPtr<USceneComponent> DefaultScene;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component", meta = (AllowPrivateAccess = "true"))
    TObjectPtr<UStaticMeshComponent> DisplayMesh;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component", meta = (AllowPrivateAccess = "true"))
    TObjectPtr<UWidgetComponent> WidgetComponent;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component", meta = (AllowPrivateAccess = "true"))
    TObjectPtr<USphereComponent> OverlapSphere;

public:
    AInteractableActor(const FObjectInitializer& ObjectInitializer);

public:
    FORCEINLINE USceneComponent* GetDefaultScene() const { return DefaultScene; }
    FORCEINLINE UStaticMeshComponent* GetDisplayMesh() const { return DisplayMesh; }
    FORCEINLINE UWidgetComponent* GetWidgetComponent() const { return WidgetComponent; }
    FORCEINLINE USphereComponent* GetOverlapSphere() const { return OverlapSphere; }
};
