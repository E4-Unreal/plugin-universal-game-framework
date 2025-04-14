// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Types/ItemContainer.h"
#include "ItemActorBase.generated.h"

UCLASS()
class ITEMSYSTEM_API AItemActorBase : public AActor
{
    GENERATED_BODY()

protected:
    static FName DisplayMeshName;

private:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component", meta = (AllowPrivateAccess = "true"))
    TObjectPtr<UStaticMeshComponent> DisplayMesh;

protected:
    UPROPERTY(EditAnywhere, Category = "Config")
    FItemContainer ItemData;

public:
    AItemActorBase(const FObjectInitializer& ObjectInitializer);

    FORCEINLINE UStaticMeshComponent* GetDisplayMesh() const { return DisplayMesh; }
};
