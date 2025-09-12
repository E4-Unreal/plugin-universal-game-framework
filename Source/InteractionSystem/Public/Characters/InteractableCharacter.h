// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InteractableCharacterBase.h"
#include "InteractableCharacter.generated.h"

class UWidgetComponent;
class USphereComponent;

UCLASS(Abstract)
class INTERACTIONSYSTEM_API AInteractableCharacter : public AInteractableCharacterBase
{
    GENERATED_BODY()

protected:
    static FName WidgetComponentName;
    static FName OverlapSphereName;

private:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component", meta = (AllowPrivateAccess = "true"))
    TObjectPtr<UWidgetComponent> WidgetComponent;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component", meta = (AllowPrivateAccess = "true"))
    TObjectPtr<USphereComponent> OverlapSphere;

public:
    AInteractableCharacter(const FObjectInitializer& ObjectInitializer);

    /* Actor */

    virtual void PreInitializeComponents() override;

public:
    FORCEINLINE UWidgetComponent* GetWidgetComponent() const { return WidgetComponent; }
    FORCEINLINE USphereComponent* GetOverlapSphere() const { return OverlapSphere; }
};
