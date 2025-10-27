// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "FootstepManagerComponent.generated.h"


class UHitEffectDefinition;

UCLASS(meta = (BlueprintSpawnableComponent))
class EFFECTMANAGER_API UFootstepManagerComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
    TEnumAsByte<ECollisionChannel> TraceChannel;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
    float TraceDistance;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
    TObjectPtr<UHitEffectDefinition> HitEffectDefinition;

protected:
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Reference", Transient)
    TWeakObjectPtr<USkeletalMeshComponent> RootMesh;

public:
    UFootstepManagerComponent();

    UFUNCTION(BlueprintCallable)
    virtual void SetRootMesh(USkeletalMeshComponent* NewRootMesh);

    UFUNCTION(BlueprintCallable)
    virtual void SpawnEffect(FName SocketName);

protected:
    virtual void FindRootMesh();

    virtual UHitEffectDefinition* GetHitEffectDefinition() const;
};
