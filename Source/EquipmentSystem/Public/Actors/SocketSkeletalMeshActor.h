// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SocketMeshActor.h"
#include "SocketSkeletalMeshActor.generated.h"

UCLASS()
class EQUIPMENTSYSTEM_API ASocketSkeletalMeshActor : public ASocketMeshActor
{
    GENERATED_BODY()

public:
    ASocketSkeletalMeshActor(const FObjectInitializer& ObjectInitializer);

    virtual void SetMesh(UStreamableRenderAsset* NewMesh) override;

    UFUNCTION(BlueprintCallable)
    void SetSkeletalMesh(USkeletalMesh* NewMesh, bool bReinitPose = true);
};
